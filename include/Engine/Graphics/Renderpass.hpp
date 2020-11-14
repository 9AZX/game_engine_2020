#pragma once

#ifndef Renderpass_HPP_
#define Renderpass_HPP_

#include <vulkan/vulkan.hpp>
#include <array>

class Renderpass
{
public:
	Renderpass();
	~Renderpass();

	vk::RenderPass renderPass;

	void createRenderPass(vk::Format swapChainImageFormat);

	void beginRenderPass(std::array<vk::ClearValue, 1> clearValues, vk::CommandBuffer commandBuffer, vk::Framebuffer swapChainFrameBuffer, vk::Extent2D swapChainImageExtent);
	void endRenderPass(VkCommandBuffer commandBuffer);
};

#endif /* Renderpass_HPP_ */