#include "Engine/Graphics/Renderpass.hpp"
#include "Engine/Graphics.hpp"

Renderpass::Renderpass() {}


Renderpass::~Renderpass() {}


void Renderpass::createRenderPass(vk::Format swapChainImageFormat)
{
	std::array<vk::AttachmentDescription, 1> attachmentDescriptions;
	attachmentDescriptions[0] = vk::AttachmentDescription(vk::AttachmentDescriptionFlags(),
		swapChainImageFormat,
		vk::SampleCountFlagBits::e1,
		vk::AttachmentLoadOp::eClear,
		vk::AttachmentStoreOp::eStore,
		vk::AttachmentLoadOp::eDontCare,
		vk::AttachmentStoreOp::eDontCare,
		vk::ImageLayout::eUndefined,
		vk::ImageLayout::ePresentSrcKHR);

	vk::AttachmentReference colorReference(0, vk::ImageLayout::eColorAttachmentOptimal);
	vk::SubpassDescription subpass(
		vk::SubpassDescriptionFlags(), vk::PipelineBindPoint::eGraphics, {}, colorReference);

	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createRenderPassUnique(
		vk::RenderPassCreateInfo(vk::RenderPassCreateFlags(), attachmentDescriptions, subpass));
}

void Renderpass::beginRenderPass(std::array<vk::ClearValue, 1> clearValues,
	vk::CommandBuffer commandBuffer,
	vk::Framebuffer swapChainFrameBuffer,
	vk::Extent2D swapChainImageExtent)
{
	vk::Rect2D size(0, swapChainImageExtent);

	vk::RenderPassBeginInfo brp(
		renderPass,
		swapChainFrameBuffer,
		size,
		static_cast<uint32_t>(clearValues.size()),
		clearValues.data()
		);

	commandBuffer.beginRenderPass(brp, vk::SubpassContents::eInline);
}

void Renderpass::endRenderPass(VkCommandBuffer commandBuffer)
{
	vkCmdEndRenderPass(commandBuffer);
}

void Renderpass::destroy()
{
	vkDestroyRenderPass(Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get(), renderPass, nullptr);
}