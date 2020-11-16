#ifndef ENGINE_GRAPHICS_HPP_
#define ENGINE_GRAPHICS_HPP_

#include "Engine/Graphics/DebugMessenger.hpp"
#include "Engine/Graphics/Device.hpp"
#include "Engine/Graphics/Instance.hpp"
#include "Engine/Graphics/Swapchain.hpp"
#include "Engine/Graphics/Renderpass.hpp"
#include "Engine/Graphics/RenderTarget.hpp"
#include "Engine/Graphics/CommandBuffer.hpp"
#include "Engine/Graphics/GraphicsPipeline.hpp"
#include "Engine/Graphics/ObjectBuffers.hpp"
#include "Engine/Graphics/Descriptor.hpp"

#include <vulkan/vulkan.hpp>

namespace Engine {

class Graphics
{
public:
    Graphics() {}
    Graphics(
        std::string name,
        std::shared_ptr<Engine::Window> window,
        bool enableDebugging
    );
    ~Graphics();

    std::shared_ptr<Instance> gInstance;
    std::shared_ptr<Device> gDevice;
    std::shared_ptr<Swapchain> gSwapChain;
    std::shared_ptr<Renderpass> gRenderpass;
    std::shared_ptr<RenderTarget> gRenderTarget;
    std::shared_ptr<CommandBuffer> gCommandBuffer;
    std::shared_ptr<GraphicsPipeline> gGraphicsPipeline;
    std::shared_ptr<ObjectBuffers> gObjectBuffers;
    std::shared_ptr<Descriptor> gDescriptor;

    DebugMessenger messenger;

    static std::shared_ptr<Graphics> graphics;

    static std::shared_ptr<Graphics> getInstance();

    std::shared_ptr<Device> getDevice();

    std::shared_ptr<Swapchain> getSwapchain();
    std::shared_ptr<Renderpass> getRenderpass();
    vk::UniqueCommandBuffer currentCommandBuffer;

private:
    bool _enableDebugging;
    std::string _appName;

    std::shared_ptr<Engine::Window> _window;

    const int MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<vk::Fence> inFlightFences;
    vk::Semaphore imageAvailableSemaphore;
    vk::Semaphore renderFinishedSemaphore;

#if !defined(NDEBUG)
    //TODO #8 Vulkan message debuging
#endif
}; /* class Graphics */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_HPP_ */
