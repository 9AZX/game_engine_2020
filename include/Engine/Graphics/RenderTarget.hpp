#pragma once

#ifndef RenderTarget_HPP_
#define RenderTarget_HPP_

#include <vulkan/vulkan.hpp>
#include <vector>
#include <array>

class RenderTarget
{
public:
    RenderTarget();
    ~RenderTarget();

	std::vector<vk::Image> _swapChainImages;
	vk::Extent2D _swapChainImageExtent;

	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	void createViewsAndFramebuffer(std::vector<vk::Image> swapChainImages, vk::Format swapChainImageFormat, vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass);

	void createImageViews(vk::Format swapChainImageFormat);
	void createFrameBuffer(vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass);
};


#endif /* RenderTarget_HPP_ */
