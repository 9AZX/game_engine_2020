#pragma once

#ifndef RenderTarget_HPP_
#define RenderTarget_HPP_

#include <vulkan/vulkan.hpp>
#include <vector>
#include <array>

#include "Engine/Graphics/Swapchain.hpp"
#include "Engine/Graphics/Device.hpp"

namespace Engine
{
class RenderTarget
{
public:
    RenderTarget(std::shared_ptr<Swapchain> gSwapChain, vk::RenderPass renderPass, std::shared_ptr<Device> gdevice);
    ~RenderTarget();

	std::vector<vk::Image> _swapChainImages;
	vk::Extent2D _swapChainImageExtent;

	std::vector<vk::UniqueImageView> swapChainImageViews;
	std::vector<vk::Framebuffer> swapChainFramebuffers;

	void createImageViews(vk::Format swapChainImageFormat);
	void createFrameBuffer(vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass);

	void destroy();

private:
	std::shared_ptr<Swapchain> _swapChain;
	std::shared_ptr<Device> _device;
};
}

#endif /* RenderTarget_HPP_ */
