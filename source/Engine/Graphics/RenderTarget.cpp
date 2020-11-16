#include "Engine/Graphics/RenderTarget.hpp"
#include "Engine/Graphics/VkTools.hpp"

Engine::RenderTarget::RenderTarget(std::shared_ptr<Swapchain> gSwapChain, vk::RenderPass renderPass, std::shared_ptr<Device> gdevice) 
	: _swapChain(gSwapChain), _device(gdevice)
{
	_swapChainImages = _swapChain->swapChainImages;
	_swapChainImageExtent = _swapChain->swapChainImageExtent;

	//createImageViews(_swapChain->swapChainImageFormat);
	createFrameBuffer(_swapChain->swapChainImageExtent, renderPass);
}

Engine::RenderTarget::~RenderTarget() {}


void Engine::RenderTarget::createImageViews(vk::Format swapChainImageFormat)
{
	swapChainImageViews.resize(_swapChainImages.size());

	for (size_t i = 0; i < _swapChainImages.size(); i++) {
		swapChainImageViews[i] = vkTools::createImageView(_swapChainImages[i], swapChainImageFormat,
			vk::ImageAspectFlagBits::eColor, _device);
	}
}

void Engine::RenderTarget::createFrameBuffer(vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass) {

	swapChainFramebuffers.resize(swapChainImageViews.size());

	for (size_t i = 0; i < swapChainImageViews.size(); i++)
	{

		std::array<vk::ImageView, 1> attachments = {
			swapChainImageViews[i].get(),
		};

		vk::FramebufferCreateInfo fbInfo(vk::FramebufferCreateFlags(),
			renderPass,
			static_cast<uint32_t>(attachments.size()),
			attachments.data(),
			swapChainImageExtent.width,
			swapChainImageExtent.height,
			1);

		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createFramebufferUnique(fbInfo);
	}
}

void Engine::RenderTarget::destroy()
{
	for (auto &imageView : swapChainImageViews) {
		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyImageView(imageView.get());
	}

	for (auto framebuffer : swapChainFramebuffers) {
		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyFramebuffer(framebuffer);
	}
}

