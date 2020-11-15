#pragma once

#include <vulkan\vulkan.hpp>
#include <stdexcept>
#include <vector>

#include "Engine/Graphics.hpp"

namespace vkTools
{
	vk::UniqueImageView createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags);

	void createBuffer(vk::DeviceSize size,
		vk::BufferUsageFlags usage,
		vk::MemoryPropertyFlags propertyFlags,
		vk::UniqueBuffer& buffer,
		vk::DeviceMemory bufferMemory);

	uint32_t findMemoryTypeIndex(uint32_t typeFilter, vk::MemoryPropertyFlags properties);

	vk::UniqueCommandBuffer beginSingleTimeCommands(vk::UniqueCommandPool commandPool);

	void endSingleTimeCommands(vk::UniqueCommandBuffer& commandBuffer,
		vk::UniqueCommandPool commandPool);

	void copyBuffer(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size);
}