#include "Engine/Graphics/Renderpass.hpp"
#include "Engine/Graphics.hpp"
#include <iostream>

Engine::Renderpass::Renderpass(std::shared_ptr<Engine::Device> gDevice, std::shared_ptr<Engine::Swapchain> gSwapChain)
	:_device(gDevice), _swapchain(gSwapChain)
{
	vk::AttachmentDescription colorAttachment(vk::AttachmentDescriptionFlags(),
		_swapchain->swapChainImageFormat,
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

	std::array<vk::AttachmentDescription, 1> attachment = { colorAttachment };

	renderPass = _device->getUniqueDevice()->get().createRenderPass(
		vk::RenderPassCreateInfo(vk::RenderPassCreateFlags(), attachment, subpass));
}

Engine::Renderpass::~Renderpass() {}


void Engine::Renderpass::beginRenderPass(std::array<vk::ClearValue, 1> clearValues,
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

void Engine::Renderpass::endRenderPass(VkCommandBuffer commandBuffer)
{
	vkCmdEndRenderPass(commandBuffer);
}

void Engine::Renderpass::destroy()
{
	vkDestroyRenderPass(_device->getUniqueDevice()->get(), renderPass, nullptr);
}