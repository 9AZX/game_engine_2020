#include "Engine/Graphics/CommandBuffer.hpp"
#include "Engine/Graphics.hpp"
#include "Engine/Graphics/Device.hpp"

Engine::CommandBuffer::CommandBuffer(std::shared_ptr<Engine::Device> device) : _device(device)
{
}

Engine::CommandBuffer::~CommandBuffer()
{
}

void Engine::CommandBuffer::createCommandPoolAndBuffer(size_t imageCount)
{
	createCommandPool();
	allocateCommandBuffers(imageCount);
}

void Engine::CommandBuffer::createCommandPool()
{
	vk::CommandPoolCreateInfo cpInfo(vk::CommandPoolCreateFlags(), _device->graphicsQueueFamilyIndex);
	commandPool = _device->getUniqueDevice()->get().createCommandPoolUnique(cpInfo);
}

void Engine::CommandBuffer::allocateCommandBuffers(size_t imageCount)
{
	commandBuffers.resize(imageCount);
	vk::CommandBufferAllocateInfo cbInfo(commandPool.get(), vk::CommandBufferLevel::ePrimary, (uint32_t)commandBuffers.size());
	commandBuffers = _device->getUniqueDevice()->get().allocateCommandBuffers(cbInfo);
}

void Engine::CommandBuffer::beginCommandBuffer(vk::CommandBuffer &commandBuffer)
{
	vk::CommandBufferBeginInfo cbBeginInfo(vk::CommandBufferUsageFlagBits::eSimultaneousUse);
	commandBuffer.begin(cbBeginInfo);
}

void Engine::CommandBuffer::endCommandBuffer(vk::CommandBuffer &commandBuffer)
{
	commandBuffer.end();
}

void Engine::CommandBuffer::destroy()
{
	_device->getUniqueDevice()->get().destroyCommandPool(commandPool.get());
}