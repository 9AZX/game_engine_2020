#include "Engine/Graphics/ObjectBuffers.hpp"
#include "Engine/Graphics/VkTools.hpp"

ObjectBuffers::ObjectBuffers() {}

ObjectBuffers::~ObjectBuffers() {}

void ObjectBuffers::createVertexIndexUniformsBuffers(MeshType modelType)
{
	switch (modelType)
	{
	case kTriangle: Mesh::setTriData(vertices, indices);
		break;
	case kQuad: Mesh::setQuadData(vertices, indices);
		break;
	case kCube: Mesh::setCubeData(vertices, indices);
		break;
	case kSphere:
		Mesh::setSphereData(vertices, indices);
		break;
	}
	createVertexBuffer();
	createIndexBuffer();
	createUniformBuffers();
}

void ObjectBuffers::createVertexBuffer() {

	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	//-- Staging buffer creation

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	

	vkTools::createBuffer(bufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer,
		stagingBufferMemory);


	//-- Copying vertex data into the buffer
	//-- This is done with mapping the buffer memory
	void* data;
	//-- Allows us to access a region of the specified memory resource
	vkMapMemory(VulkanContext::getInstance()->getDevice()->logicalDevice,
		stagingBufferMemory,
		0, // offet
		bufferSize,// size
		0,// flag
		&data); // copy buffer memory to data 

	memcpy(data, vertices.data(), (size_t)bufferSize);

	vkUnmapMemory(VulkanContext::getInstance()->getDevice()->logicalDevice,
		stagingBufferMemory);

	// Create Vertex Buffer
	vkTools::createBuffer(bufferSize,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, 
		vertexBuffer,
		vertexBufferMemory);

	vkTools::copyBuffer(stagingBuffer,
		vertexBuffer,
		bufferSize);

	vkDestroyBuffer(VulkanContext::getInstance()->getDevice()->logicalDevice, stagingBuffer, nullptr);
	vkFreeMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, stagingBufferMemory, nullptr);

	
	vk::UniqueBuffer stagingBuffer;
	vk::UniqueDevice stagingBufferMemory;
}

void ObjectBuffers::createVertexBufferCPP()
{
	vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
	vk::UniqueBuffer stagingBuffer;
	vk::DeviceMemory stagingBufferMemory;

	vkTools::createBufferCPP(bufferSize,
		vk::BufferUsageFlagBits::eTransferSrc,
		vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
		stagingBuffer,
		stagingBufferMemory);
	
	void* data;

	data = Engine::Graphics::getInstance()->getDevice()->logicalDevice->mapMemory(stagingBufferMemory,
		0, // offet
		bufferSize);
	memcpy(data, vertices.data(), (size_t)bufferSize);

	Engine::Graphics::getInstance()->getDevice()->logicalDevice->unmapMemory(stagingBufferMemory);

	vkTools::createBufferCPP(bufferSize,
		vk::BufferUsageFlagBits::eTransferSrc | vk::BufferUsageFlagBits::eVertexBuffer,
		vk::MemoryPropertyFlagBits::eDeviceLocal,
		vertexBuffer,
		vertexBufferMemory);

	vkTools::copyBufferCPP(stagingBuffer.get(),
		vertexBuffer.get(),
		bufferSize);

	Engine::Graphics::getInstance()->getDevice()->logicalDevice->destroyBuffer(stagingBuffer.get(), nullptr);
	Engine::Graphics::getInstance()->getDevice()->logicalDevice->freeMemory(stagingBufferMemory, nullptr);
}

void ObjectBuffers::createIndexBuffer() {

	VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	vkTools::createBuffer(bufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices.data(), (size_t)bufferSize);
	vkUnmapMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, stagingBufferMemory);

	vkTools::createBuffer(bufferSize,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		indexBuffer,
		indexBufferMemory);

	vkTools::copyBuffer(stagingBuffer,
		indexBuffer,
		bufferSize);

	vkDestroyBuffer(VulkanContext::getInstance()->getDevice()->logicalDevice, stagingBuffer, nullptr);
	vkFreeMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, stagingBufferMemory, nullptr);

}

void ObjectBuffers::createIndexBufferCPP()
{
	vk::DeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	vk::UniqueBuffer stagingBuffer;
	vk::DeviceMemory stagingBufferMemory;

	vkTools::createBufferCPP(bufferSize,
		vk::BufferUsageFlagBits::eTransferSrc,
		vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
		stagingBuffer, stagingBufferMemory);
	void* data;

	data = Engine::Graphics::getInstance()->getDevice()->logicalDevice->mapMemory(stagingBufferMemory, 0, bufferSize);
	memcpy(data, indices.data(), (size_t)bufferSize);
	Engine::Graphics::getInstance()->getDevice()->logicalDevice->unmapMemory(stagingBufferMemory);

	vkTools::createBufferCPP(bufferSize,
		vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer,
		vk::MemoryPropertyFlagBits::eDeviceLocal,
		indexBuffer,
		indexBufferMemory);

	vkTools::copyBufferCPP(stagingBuffer.get(),
		indexBuffer.get(),
		bufferSize);

	Engine::Graphics::getInstance()->getDevice()->logicalDevice->destroyBuffer(stagingBuffer.get(), nullptr);
	Engine::Graphics::getInstance()->getDevice()->logicalDevice->freeMemory(stagingBufferMemory, nullptr);
}
// -- Create Uniform buffer

void ObjectBuffers::createUniformBuffers()
{

	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	vkTools::createBuffer(bufferSize,
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		uniformBuffers,
		uniformBuffersMemory);

}

void ObjectBuffers::createUniformBuffersCPP()
{
	vk::DeviceSize bufferSize = sizeof(UniformBufferObject);

	vkTools::createBufferCPP(bufferSize,
		vk::BufferUsageFlagBits::eUniformBuffer,
		vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible,
		uniformBuffers,
		uniformBuffersMemory);
}

void ObjectBuffers::destroy()
{
	vkDestroyBuffer(VulkanContext::getInstance()->getDevice()->logicalDevice, uniformBuffers, nullptr);
	vkFreeMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, uniformBuffersMemory, nullptr);

	vkDestroyBuffer(VulkanContext::getInstance()->getDevice()->logicalDevice, indexBuffer, nullptr);
	vkFreeMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, indexBufferMemory, nullptr);

	vkDestroyBuffer(VulkanContext::getInstance()->getDevice()->logicalDevice, vertexBuffer, nullptr);
	vkFreeMemory(VulkanContext::getInstance()->getDevice()->logicalDevice, vertexBufferMemory, nullptr);
}