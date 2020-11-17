#pragma once

#include <vulkan\vulkan.hpp>
#include <vector>

#include "Engine/Graphics/Device.hpp"

namespace Engine
{
class CommandBuffer
{
public:
	CommandBuffer(std::shared_ptr<Engine::Device> device);
	~CommandBuffer();
	vk::UniqueCommandPool commandPool;
	std::vector<vk::CommandBuffer> commandBuffers;
	void createCommandPoolAndBuffer(size_t imageCount);
	void beginCommandBuffer(vk::CommandBuffer &commandBuffer);
	void endCommandBuffer(vk::CommandBuffer &commandBuffer);
	void createCommandPool();
	void allocateCommandBuffers(size_t imageCount);
	void destroy();

private:
	std::shared_ptr<Engine::Device> _device;
};

}