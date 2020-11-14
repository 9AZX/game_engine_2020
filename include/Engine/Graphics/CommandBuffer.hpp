#pragma once

#include <vulkan\vulkan.hpp>
#include <vector>

class CommandBuffer
{
public:
	CommandBuffer();
	~CommandBuffer();
	vk::UniqueCommandPool commandPool;
	std::vector<vk::CommandBuffer> commandBuffers;
	void createCommandPoolAndBuffer(size_t imageCount);
	void beginCommandBuffer(vk::CommandBuffer commandBuffer);
	void endCommandBuffer(vk::CommandBuffer commandBuffer);
	void createCommandPool();
	void allocateCommandBuffers(size_t imageCount);
	void destroy();
};