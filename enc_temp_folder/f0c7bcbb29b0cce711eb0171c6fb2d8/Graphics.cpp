#include "Engine/Graphics.hpp"

#include <filesystem>
#include <fstream>

std::shared_ptr<Engine::Graphics> Engine::Graphics::graphics = nullptr;

Engine::Graphics::Graphics(
    std::string _gameName,
    std::shared_ptr<Engine::Window> window,
    bool enableDebugging
):
    _appName(_gameName),
    _window(window),
    _enableDebugging(enableDebugging)
{

    gInstance = std::make_shared<Instance>(_gameName, _enableDebugging);
    messenger.init(gInstance);
    gDevice = std::make_shared<Device>(gInstance);
    gSwapChain = std::make_shared<Swapchain>(_window, gInstance, gDevice);

    gRenderpass = std::make_shared<Renderpass>(gDevice, gSwapChain);

    gGraphicsPipeline = std::make_shared<GraphicsPipeline>(gDevice, gRenderpass);
    auto i = getInstance();
    std::string name = "vert";
    std::vector<unsigned int> v(10, 10);
    std::filesystem::path vert = "C:\\Users\\CHAUVIN\\source\\repos\\C++Vulkan\\vert.spv";
    Engine::ShaderResource shader1(name, "C:\\Users\\CHAUVIN\\source\\repos\\C++Vulkan\\vert.spv", v);
    Engine::ShaderResource shader2(name, "C:/Users/CHAUVIN/source/repos/C++Vulkan/frag.spv", v);
    gGraphicsPipeline->createGraphicsPipeline(&shader1, &shader2);

    gRenderTarget = std::make_shared<RenderTarget>(gSwapChain, gRenderpass->renderPass, gDevice);


    gDescriptor = std::make_shared<Descriptor>(gDevice);
    gDescriptor->createDescriptorLayoutSetPoolAndAllocate(gSwapChain->swapChainImages.size());


    gCommandBuffer = std::make_shared<CommandBuffer>(gDevice);
    gCommandBuffer->createCommandPoolAndBuffer(gSwapChain->swapChainImages.size());


    
    imageAvailableSemaphore = gDevice->getUniqueDevice()->get().createSemaphore(vk::SemaphoreCreateInfo(vk::SemaphoreCreateFlags()));
    renderFinishedSemaphore = gDevice->getUniqueDevice()->get().createSemaphore(vk::SemaphoreCreateInfo(vk::SemaphoreCreateFlags()));
    inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
    {
        inFlightFences[i] = gDevice->getUniqueDevice()->get().createFence(vk::FenceCreateInfo());
    }
}

Engine::Graphics::~Graphics()
{
}

void Engine::Graphics::DrawStart()
{
    vk::ResultValue<uint32_t> 
        currentBuffer = gDevice->getUniqueDevice()->get().acquireNextImageKHR(
            gSwapChain->swapchain.get(),
            std::numeric_limits<uint64_t>::max(),
            imageAvailableSemaphore,
            nullptr
            );
    gDevice->getUniqueDevice()->get().waitForFences(inFlightFences, VK_TRUE, 100000000);
    gDevice->getUniqueDevice()->get().resetFences(inFlightFences);

    currentCommandBuffer = gCommandBuffer->commandBuffers[currentBuffer];
    gCommandBuffer->beginCommandBuffer(currentCommandBuffer);

    vk::ClearValue clearcolor(std::array<float, 4>({ { 0.2f, 0.2f, 0.2f, 0.2f } }));
    std::array<vk::ClearValue, 1> clearValues = { clearcolor };

    gRenderpass->beginRenderPass(clearValues, currentCommandBuffer, 
        gRenderTarget->swapChainFramebuffers[currentBuffer],
        gRenderTarget->_swapChainImageExtent);

}

void Engine::Graphics::DrawEnd()
{
    gRenderpass->endRenderPass(currentCommandBuffer);
    gCommandBuffer->endCommandBuffer(currentCommandBuffer);

    vk::PipelineStageFlags waitDestinationStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
    vk::SubmitInfo submitInfo(imageAvailableSemaphore, waitDestinationStageMask, currentCommandBuffer);

    gDevice->graphicsQueue.submit(submitInfo, inFlightFences[indexImage]);

    vk::PresentInfoKHR presentInfo({}, gSwapChain->swapchain.get(), indexImage);

    gDevice->presentQueue.presentKHR(presentInfo);
    gDevice->presentQueue.waitIdle();
}

std::shared_ptr<Engine::Graphics> Engine::Graphics::getInstance()
{
    if (!graphics)
    {
        graphics = std::shared_ptr<Graphics>();
    }
    return graphics;
}

std::shared_ptr<Engine::Device> Engine::Graphics::getDevice()
{
    return gDevice;
}

std::shared_ptr<Engine::Swapchain> Engine::Graphics::getSwapchain()
{
    return gSwapChain;
}

std::shared_ptr<Engine::Renderpass> Engine::Graphics::getRenderpass()
{
    return gRenderpass;
}
