#include "Engine/Graphics/RenderTarget.hpp"
#include "Engine/Graphics/VkTools.hpp"

RenderTarget::RenderTarget() {}

RenderTarget::~RenderTarget() {}

void RenderTarget::createViewsAndFramebuffer(std::vector<vk::Image> swapChainImages, vk::Format swapChainImageFormat, vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass) {

	_swapChainImages = swapChainImages;
	_swapChainImageExtent = swapChainImageExtent;

	createImageViews(swapChainImageFormat);
	createFrameBuffer(swapChainImageExtent, renderPass);
}

void RenderTarget::createImageViews(vk::Format swapChainImageFormat) {

	swapChainImageViews.resize(_swapChainImages.size());

	for (size_t i = 0; i < _swapChainImages.size(); i++) {
		swapChainImageViews[i] = vkTools::createImageView(_swapChainImages[i], swapChainImageFormat,
			vk::ImageAspectFlagBits::eColor);
	}
}

void RenderTarget::createFrameBuffer(vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass) {

	swapChainFramebuffers.resize(swapChainImageViews.size());

	for (size_t i = 0; i < swapChainImageViews.size(); i++) {

		std::array<vk::ImageView, 1> attachments = {
			swapChainImageViews[i],
		};

		vk::FramebufferCreateInfo fbInfo(vk::FramebufferCreateFlags(),
			renderPass,
			attachments,
			swapChainImageExtent.width,
			swapChainImageExtent.height,
			1);

		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createFramebufferUnique(fbInfo);
			
	}
}

RenderTarget::~RenderTarget()
{
	for (auto imageView : swapChainImageViews) {
		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyImageView(imageView);
	}

	for (auto framebuffer : swapChainFramebuffers) {
		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyFramebuffer(framebuffer);
	}
}

