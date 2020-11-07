#pragma once

#include <vulkan\vulkan.hpp>
#include <stdexcept>
#include <vector>

#include "Engine/Graphics.hpp"

namespace vkTools
{
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	vk::UniqueImageView createImageViewCPP(vk::Image image, vk::Format format, vk::ImageAspectFlags aspectFlags);

	void createBuffer(VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VkBuffer& buffer,
		VkDeviceMemory& bufferMemory);

	void createBufferCPP(vk::DeviceSize size,
		vk::BufferUsageFlags usage,
		vk::MemoryPropertyFlags propertyFlags,
		vk::UniqueBuffer& buffer,
		vk::DeviceMemory bufferMemory);

	uint32_t findMemoryTypeIndex(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	uint32_t findMemoryTypeIndexCPP(uint32_t typeFilter, vk::MemoryPropertyFlags properties);

	VkCommandBuffer beginSingleTimeCommands(VkCommandPool commandPool);
	vk::UniqueCommandBuffer beginSingleTimeCommandsCPP(vk::UniqueCommandPool commandPool);

	void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool);
	void endSingleTimeCommandsCPP(vk::UniqueCommandBuffer& commandBuffer,
		vk::UniqueCommandPool commandPool);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void copyBufferCPP(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size);
}