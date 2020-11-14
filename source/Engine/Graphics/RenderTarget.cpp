#include "Engine/Graphics/RenderTarget.hpp"

RenderTarget::RenderTarget() {}

RenderTarget::~RenderTarget() {}

void RenderTarget::createViewsAndFramebuffer(std::vector<VkImage> swapChainImages, VkFormat swapChainImageFormat, vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass) {

	_swapChainImages = swapChainImages;
	_swapChainImageExtent = swapChainImageExtent;

	createImageViews(swapChainImageFormat);
	createFrameBuffer(swapChainImageExtent, renderPass);
}

void RenderTarget::createImageViews(VkFormat swapChainImageFormat) {

	swapChainImageViews.resize(_swapChainImages.size());

	for (size_t i = 0; i < _swapChainImages.size(); i++) {

		swapChainImageViews[i] = vkTools::createImageView(_swapChainImages[i],
			swapChainImageFormat,
			VK_IMAGE_ASPECT_COLOR_BIT);
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

		if (VulkanContext::getInstance()->getDevice()->logicalDevice->createFramebufferUnique(&fbInfo)) {

			throw std::runtime_error(" failed to create framebuffers !!!");
		}
	}
}


void RenderTarget::destroy() {

	// image views
	for (auto imageView : swapChainImageViews) {

		vkDestroyImageView(VulkanContext::getInstance()->getDevice()->logicalDevice, imageView, nullptr);
	}

	// Framebuffers
	for (auto framebuffer : swapChainFramebuffers) {
		vkDestroyFramebuffer(VulkanContext::getInstance()->getDevice()->logicalDevice, framebuffer, nullptr);
	}

}
