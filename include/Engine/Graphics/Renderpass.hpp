#pragma once

#ifndef Renderpass_HPP_
#define Renderpass_HPP_

#include <vulkan/vulkan.hpp>
#include <array>

#include "Engine/Graphics/Device.hpp"
#include "Engine/Graphics/SwapChain.hpp"

namespace Engine {
	class Renderpass
	{
	public:
		Renderpass(std::shared_ptr<Engine::Device> gDevice, std::shared_ptr<Engine::Swapchain> gSwapChain);
		~Renderpass();

		vk::RenderPass renderPass;

		void beginRenderPass(std::array<vk::ClearValue, 1> clearValues, vk::CommandBuffer commandBuffer, vk::Framebuffer swapChainFrameBuffer, vk::Extent2D swapChainImageExtent);
		void endRenderPass(VkCommandBuffer commandBuffer);
		void destroy();

	private:
		std::shared_ptr<Engine::Device> _device;
		std::shared_ptr<Engine::Swapchain> _swapchain;
	};
}
#endif /* Renderpass_HPP_ */