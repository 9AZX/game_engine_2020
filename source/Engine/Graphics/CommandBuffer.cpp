#include "Engine/Graphics/CommandBuffer.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/Graphics/Device.hpp"

CommandBuffer::CommandBuffer() {}
CommandBuffer::~CommandBuffer() {}

void CommandBuffer::createCommandPoolAndBuffer(size_t imageCount)
{
	createCommandPool();
	allocateCommandBuffers(imageCount);
}

void CommandBuffer::createCommandPool()
{
	Engine::QueueFamilyIndices qFamilyIndices = Engine::Graphics::getInstance()->getDevice()->getQueueFamiliesIndicesOfCurrentDevice();

	vk::CommandPoolCreateInfo cpInfo(vk::CommandPoolCreateFlags(), qFamilyIndices.graphicsFamily);
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createCommandPool(cpInfo);
}

void CommandBuffer::allocateCommandBuffers(size_t imageCount)
{
	commandBuffers.resize(imageCount);
	vk::CommandBufferAllocateInfo cbInfo(commandPool.get(), vk::CommandBufferLevel::ePrimary, (uint32_t)commandBuffers.size());
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().allocateCommandBuffers(cbInfo);
}

void CommandBuffer::beginCommandBuffer(vk::CommandBuffer commandBuffer)
{
	vk::CommandBufferBeginInfo cbBeginInfo(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
	commandBuffer.begin(cbBeginInfo);
}

void CommandBuffer::endCommandBuffer(vk::CommandBuffer commandBuffer)
{
	commandBuffer.end();
}

void CommandBuffer::destroy()
{
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyCommandPool(commandPool.get());
}