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

	std::vector<VkImage> _swapChainImages;
	vk::Extent2D _swapChainImageExtent;

	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	VkFormat depthFormat;

	void createViewsAndFramebuffer(std::vector<VkImage> swapChainImages, VkFormat swapChainImageFormat, vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass);

	void createImageViews(VkFormat swapChainImageFormat);
	void createFrameBuffer(vk::Extent2D swapChainImageExtent, vk::RenderPass renderPass);


	void destroy();
};


#endif /* RenderTarget_HPP_ */
