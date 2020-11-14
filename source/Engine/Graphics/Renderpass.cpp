#include "Engine/Graphics/Renderpass.hpp"

Renderpass::Renderpass() {}


Renderpass::~Renderpass() {}


void Renderpass::createRenderPass(vk::Format swapChainImageFormat) {

	// Tell vulkan the swapchain framebuffer attachments we will be using
	// How many color buffers and depth buffers and 
	// How many samples to use for each of them;

	std::array<vk::AttachmentDescription, 2> attachmentDescriptions;
	attachmentDescriptions[0] = vk::AttachmentDescription(vk::AttachmentDescriptionFlags(),
		swapChainImageFormat,
		vk::SampleCountFlagBits::e1,
		vk::AttachmentLoadOp::eClear,
		vk::AttachmentStoreOp::eStore, // NOT SURE
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::ePresentSrcKHR);

	vk::AttachmentReference colorReference(0, vk::ImageLayout::eColorAttachmentOptimal);
	vk::AttachmentReference depthReference(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);
	vk::SubpassDescription  subpass(
		vk::SubpassDescriptionFlags(), vk::PipelineBindPoint::eGraphics, {}, colorReference, {}, &depthReference);

	vk::UniqueRenderPass renderPass = device->createRenderPassUnique(
		vk::RenderPassCreateInfo(vk::RenderPassCreateFlags(), attachmentDescriptions, subpass));
}

void Renderpass::beginRenderPass(std::array<vk::ClearValue, 1> clearValues,
	vk::CommandBuffer commandBuffer,
	vk::Framebuffer swapChainFrameBuffer,
	vk::Extent2D swapChainImageExtent) {
	vk::Rect2D size(300,200);

	vk::RenderPassBeginInfo brp(
		renderPass,
		swapChainFrameBuffer,
		size,
		clearValues.size(),
		clearValues.data()
		);

	commandBuffer.beginRenderPass(brp, vk::SubpassContents::eInline);
}

void Renderpass::endRenderPass(VkCommandBuffer commandBuffer) {

	vkCmdEndRenderPass(commandBuffer);
}

void Renderpass::destroy() {

	vkDestroyRenderPass(VulkanContext::getInstance()->getDevice()->logicalDevice, renderPass, nullptr);

}