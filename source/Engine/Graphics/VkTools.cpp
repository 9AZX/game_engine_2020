#include "Engine/Graphics/VkTools.hpp"
#include "Engine/Graphics/Device.hpp"

namespace vkTools {
	vk::UniqueImageView createImageViewCPP(vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags)
	{
		vk::ComponentMapping componentMapping(
			vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA);
		vk::ImageViewCreateInfo viewInfo(vk::ImageViewCreateFlags(), image, vk::ImageViewType::e2D, format, componentMapping, vk::ImageSubresourceRange(aspectFlags, 0, 1, 0, 1));

		return Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createImageViewUnique(viewInfo);
	}

	void createBuffer(vk::DeviceSize size, 
		vk::BufferUsageFlags usage, 
		vk::MemoryPropertyFlags propertyFlags, 
		vk::UniqueBuffer &buffer, 
		vk::DeviceMemory bufferMemory)
	{
		vk::BufferCreateInfo bufferInfo(vk::BufferCreateFlags(), size, usage, vk::SharingMode::eExclusive);

		buffer = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createBufferUnique(bufferInfo);
		
		vk::MemoryRequirements memrequirements = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().getBufferMemoryRequirements(buffer.get());

		vk::MemoryAllocateInfo allocInfo(memrequirements.size, findMemoryTypeIndex(memrequirements.memoryTypeBits, propertyFlags));
		bufferMemory = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().allocateMemory(allocInfo);
		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().bindBufferMemory(buffer.get(), bufferMemory, 0);
	}

	uint32_t findMemoryTypeIndex(uint32_t typeFilter, vk::MemoryPropertyFlags properties)
	{
		uint32_t typeIndex = uint32_t(~0);
		vk::PhysicalDeviceMemoryProperties memoryProperties = Engine::Graphics::getInstance()->getDevice()->getPhysicalDevice()->getMemoryProperties();

		for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
		{
			if ((typeFilter & 1) &&
				((memoryProperties.memoryTypes[i].propertyFlags & properties) == properties))
			{
				typeIndex = i;
				break;
			}
			typeFilter >>= 1;
		}
		assert(typeIndex != uint32_t(~0));
		return typeIndex;
	}

	vk::UniqueCommandBuffer beginSingleTimeCommands(vk::UniqueCommandPool commandPool)
	{
		vk::CommandBufferAllocateInfo allocInfo(commandPool.get(), vk::CommandBufferLevel::ePrimary, 1);
		
		vk::UniqueCommandBuffer commandBuffer = std::move(Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().allocateCommandBuffersUnique(allocInfo).front());

		commandBuffer->begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlags()));

		return commandBuffer;
	}

	void endSingleTimeCommandsCPP(vk::UniqueCommandBuffer &commandBuffer, 
		vk::UniqueCommandPool commandPool)
	{
		commandBuffer->end();
		vk::UniqueFence fence = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createFenceUnique(vk::FenceCreateInfo());
		vk::SubmitInfo submitInfo = vk::SubmitInfo({}, {}, *commandBuffer);

		Engine::Graphics::getInstance()->getDevice()->graphicsQueue.submit(submitInfo, fence.get());
		Engine::Graphics::getInstance()->getDevice()->graphicsQueue.waitIdle();
		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().freeCommandBuffers(commandPool.get(), *commandBuffer);
	}

	void copyBuffer(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size)
	{
		Engine::QueueFamilyIndices qFamilyIndices = Engine::Graphics::getInstance()->getDevice()->getQueueFamiliesIndicesOfCurrentDevice();

		vk::CommandPoolCreateInfo cpInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer, qFamilyIndices.graphicsFamily);

		vk::UniqueCommandPool commandPool = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().createCommandPoolUnique(cpInfo);
		vk::UniqueCommandBuffer commandBuffer = beginSingleTimeCommands(std::move(commandPool));

		vk::BufferCopy copyRegion(0, 0, size);
		commandBuffer->copyBuffer(srcBuffer, dstBuffer, 1, &copyRegion);

		endSingleTimeCommandsCPP(commandBuffer, std::move(commandPool));
		Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyCommandPool(commandPool.get(), nullptr);
	}
}