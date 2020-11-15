#include "Engine/Graphics/ObjectBuffers.hpp"
#include "Engine/Graphics/VkTools.hpp"
#include "Engine/Maths/Matrix4.hpp"

struct UniformBufferObject
{
	Engine::Math::Matrix4 model;
	Engine::Math::Matrix4 view;
	Engine::Math::Matrix4 proj;
};

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

void ObjectBuffers::createVertexBuffer()
{
	vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
	vk::UniqueBuffer stagingBuffer;
	vk::DeviceMemory stagingBufferMemory;

	vkTools::createBuffer(bufferSize,
		vk::BufferUsageFlagBits::eTransferSrc,
		vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
		stagingBuffer,
		stagingBufferMemory);
	
	void* data;

	data = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().mapMemory(stagingBufferMemory,
		0, // offet
		bufferSize);
	memcpy(data, vertices.data(), (size_t)bufferSize);

	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().unmapMemory(stagingBufferMemory);

	vkTools::createBuffer(bufferSize,
		vk::BufferUsageFlagBits::eTransferSrc | vk::BufferUsageFlagBits::eVertexBuffer,
		vk::MemoryPropertyFlagBits::eDeviceLocal,
		vertexBuffer,
		vertexBufferMemory);

	vkTools::copyBuffer(stagingBuffer.get(),
		vertexBuffer.get(),
		bufferSize);

	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyBuffer(stagingBuffer.get(), nullptr);
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().freeMemory(stagingBufferMemory, nullptr);
}

void ObjectBuffers::createIndexBuffer()
{
	vk::DeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	vk::UniqueBuffer stagingBuffer;
	vk::DeviceMemory stagingBufferMemory;

	vkTools::createBuffer(bufferSize,
		vk::BufferUsageFlagBits::eTransferSrc,
		vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
		stagingBuffer, stagingBufferMemory);
	void* data;

	data = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().mapMemory(stagingBufferMemory, 0, bufferSize);
	memcpy(data, indices.data(), (size_t)bufferSize);
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().unmapMemory(stagingBufferMemory);

	vkTools::createBuffer(bufferSize,
		vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer,
		vk::MemoryPropertyFlagBits::eDeviceLocal,
		indexBuffer,
		indexBufferMemory);

	vkTools::copyBuffer(stagingBuffer.get(),
		indexBuffer.get(),
		bufferSize);

	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyBuffer(stagingBuffer.get(), nullptr);
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().freeMemory(stagingBufferMemory, nullptr);
}

void ObjectBuffers::createUniformBuffers()
{
	vk::DeviceSize bufferSize = sizeof(UniformBufferObject);

	vkTools::createBuffer(bufferSize,
		vk::BufferUsageFlagBits::eUniformBuffer,
		vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eHostVisible,
		uniformBuffers,
		uniformBuffersMemory);
}

void ObjectBuffers::destroy()
{
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyBuffer(uniformBuffers.get(), nullptr);
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().freeMemory(uniformBuffersMemory, nullptr);

	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyBuffer(indexBuffer.get(), nullptr);
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().freeMemory(indexBufferMemory, nullptr);

	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().destroyBuffer(vertexBuffer.get(), nullptr);
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().freeMemory(vertexBufferMemory, nullptr);
}