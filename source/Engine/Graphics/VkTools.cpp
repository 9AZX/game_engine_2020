#include "Engine/Graphics/VkTools.hpp"
#include "Engine/Graphics/Device.hpp"

namespace vkTools {
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags)
	{
		VkImageViewCreateInfo viewInfo = {};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = image;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = format;
		viewInfo.subresourceRange.aspectMask = aspectFlags;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;

		VkImageView imageView;
		if (vkCreateImageView(VulkanContext::getInstance()->getDevice()->logicalDevice, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create texture imageview !");
		}
		return imageView;
	}

	vk::UniqueImageView createImageViewCPP(vk::Image image, vk::Format format, vk::ImageAspectFlags aspectFlags)
	{
		vk::ComponentMapping componentMapping(
			vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA);
		vk::ImageViewCreateInfo viewInfo(vk::ImageViewCreateFlags(), image, vk::ImageViewType::e2D, format, componentMapping, vk::ImageSubresourceRange(aspectFlags, 0, 1, 0, 1));

		return Engine::Graphics::getInstance()->getDevice()->logicalDevice->createImageViewUnique(viewInfo);
	}

	void createBuffer(VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VkBuffer& buffer, // output
		VkDeviceMemory& bufferMemory) { // output

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;// can specify multiple purposes with bitwise operation
								 // like the swap chain the buffer can be shared between different queues like ghraphics and compute
								 // Here it is exclusive to graphics
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(VulkanContext::getInstance()->getDevice()->logicalDevice, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {

			throw std::runtime_error(" failed to create vertex buffer ");
		}


		//-- Get Memory requirements for the vertexBuffer
		VkMemoryRequirements memrequirements;
		vkGetBufferMemoryRequirements(VulkanContext::getInstance()->getDevice()->logicalDevice, buffer, &memrequirements);

		//-- Memory Allocation
		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memrequirements.size;
		allocInfo.memoryTypeIndex = findMemoryTypeIndex(memrequirements.memoryTypeBits, properties);

		//VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | // can we map memory so that we can write it from CPU
		//VK_MEMORY_PROPERTY_HOST_COHERENT_BIT); // Memory is a coherent bit

		if (vkAllocateMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {

			throw std::runtime_error("failed to allocate vertex buffer memory");
		}

		//-- memory allocation was successful so now we can bind the buffer to the memory
		vkBindBufferMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, buffer, bufferMemory, 0);
	}

	void createBufferCPP(vk::DeviceSize size, 
		vk::BufferUsageFlags usage, 
		vk::MemoryPropertyFlags propertyFlags, 
		vk::UniqueBuffer &buffer, 
		vk::DeviceMemory bufferMemory)
	{
		vk::BufferCreateInfo bufferInfo(vk::BufferCreateFlags(), size, usage);

		buffer = Engine::Graphics::getInstance()->getDevice()->logicalDevice->createBufferUnique(bufferInfo);
		
		vk::MemoryRequirements memrequirements = Engine::Graphics::getInstance()->getDevice()->logicalDevice->getBufferMemoryRequirements(buffer.get());

		vk::MemoryAllocateInfo allocInfo(memrequirements.size, findMemoryTypeIndexCPP(memrequirements.memoryTypeBits, propertyFlags));
		vk::UniqueDeviceMemory deviceMemory = Engine::Graphics::getInstance()->getDevice()->logicalDevice->allocateMemoryUnique(allocInfo);
		Engine::Graphics::getInstance()->getDevice()->logicalDevice->bindBufferMemory(buffer.get(), deviceMemory.get(), 0);
	}

	uint32_t findMemoryTypeIndex(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{

		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(VulkanContext::getInstance()->getDevice()->physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {

			// As we also want to write to the memory

			if ((typeFilter & (1 << i)) && // if this memory type is suitable to certex buffer
				(memProperties.memoryTypes[i].propertyFlags & // memory types also specify heap and property 
					properties) // The properties define special features of the memory, like being able to map it so we can write to it from the CPU
				== properties) {

				return i;
			}
		}

		throw std::runtime_error("failed to find suitable memory type!");
	}

	uint32_t findMemoryTypeIndexCPP(uint32_t typeFilter, vk::MemoryPropertyFlags properties)
	{
		uint32_t typeIndex = uint32_t(~0);
		vk::PhysicalDeviceMemoryProperties memoryProperties = Engine::Graphics::getInstance()->getDevice()->physicalDevice.getMemoryProperties();

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


	VkCommandBuffer beginSingleTimeCommands(VkCommandPool commandPool) {

		//-- Alloc Command buffer  
		VkCommandBufferAllocateInfo allocInfo = {};

		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(VulkanContext::getInstance()->getDevice()->logicalDevice, &allocInfo, &commandBuffer);

		//-- Record command buffer

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		//start recording
		vkBeginCommandBuffer(commandBuffer, &beginInfo);

		return commandBuffer;
	}

	vk::UniqueCommandBuffer beginSingleTimeCommandsCPP(vk::UniqueCommandPool commandPool)
	{
		vk::CommandBufferAllocateInfo allocInfo(commandPool.get(), vk::CommandBufferLevel::ePrimary, 1);
		
		vk::UniqueCommandBuffer commandBuffer = std::move(Engine::Graphics::getInstance()->getDevice()->logicalDevice->allocateCommandBuffersUnique(allocInfo).front());

		commandBuffer->begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlags()));

		return commandBuffer;
	}

	void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool) {

		//-- End recording
		vkEndCommandBuffer(commandBuffer);

		//-- Execute the Command Buffer to complete the transfer
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(VulkanContext::getInstance()->getDevice()->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);

		vkQueueWaitIdle(VulkanContext::getInstance()->getDevice()->graphicsQueue);

		vkFreeCommandBuffers(VulkanContext::getInstance()->getDevice()->logicalDevice, commandPool, 1, &commandBuffer);

	}

	void endSingleTimeCommandsCPP(vk::UniqueCommandBuffer &commandBuffer, 
		vk::UniqueCommandPool commandPool)
	{
		commandBuffer->end();
		vk::UniqueFence fence = Engine::Graphics::getInstance()->getDevice()->logicalDevice->createFenceUnique(vk::FenceCreateInfo());
		vk::SubmitInfo submitInfo = vk::SubmitInfo({}, {}, *commandBuffer);

		Engine::Graphics::getInstance()->getDevice()->graphicsQueue.submit(submitInfo, fence.get());
		Engine::Graphics::getInstance()->getDevice()->graphicsQueue.waitIdle();
		Engine::Graphics::getInstance()->getDevice()->logicalDevice->freeCommandBuffers(commandPool.get(), *commandBuffer);
	}

	void copyBuffer(VkBuffer srcBuffer,
		VkBuffer dstBuffer,
		VkDeviceSize size) {

		// Create Command Pool
		VkCommandPool commandPool;

		QueueFamilyIndices qFamilyIndices = VulkanContext::getInstance()->getDevice()->getQueueFamiliesIndicesOfCurrentDevice();

		VkCommandPoolCreateInfo cpInfo = {};

		cpInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		cpInfo.queueFamilyIndex = qFamilyIndices.graphicsFamily;
		cpInfo.flags = 0;

		if (vkCreateCommandPool(VulkanContext::getInstance()->getDevice()->logicalDevice, &cpInfo, nullptr, &commandPool) != VK_SUCCESS) {
			throw std::runtime_error(" failed to create command pool !!");
		}


		//-- Memory transfer is done through command buffers

		// Allocate command buffer and start recording
		VkCommandBuffer commandBuffer = beginSingleTimeCommands(commandPool);

		//-- Copy the buffer
		VkBufferCopy copyregion = {};
		copyregion.srcOffset = 0;
		copyregion.dstOffset = 0;
		copyregion.size = size;
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyregion);

		// End recording and Execute command buffer and free command buffer
		endSingleTimeCommands(commandBuffer, commandPool);

		vkDestroyCommandPool(VulkanContext::getInstance()->getDevice()->logicalDevice, commandPool, nullptr);

	}

	void copyBufferCPP(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size)
	{
		Engine::QueueFamilyIndices qFamilyIndices = Engine::Graphics::getInstance()->getDevice()->getQueueFamiliesIndicesOfCurrentDevice();

		vk::CommandPoolCreateInfo cpInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer, qFamilyIndices.graphicsFamily);

		vk::UniqueCommandPool commandPool = Engine::Graphics::getInstance()->getDevice()->logicalDevice->createCommandPoolUnique(cpInfo);
		vk::UniqueCommandBuffer commandBuffer = beginSingleTimeCommandsCPP(std::move(commandPool));

		vk::BufferCopy copyRegion(0, 0, size);
		commandBuffer->copyBuffer(srcBuffer, dstBuffer, 1, &copyRegion);

		endSingleTimeCommandsCPP(commandBuffer, std::move(commandPool));
		Engine::Graphics::getInstance()->getDevice()->logicalDevice->destroyCommandPool(commandPool.get(), nullptr);
	}
}