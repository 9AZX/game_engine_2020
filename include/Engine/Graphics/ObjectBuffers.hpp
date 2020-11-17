#pragma once

#include <vulkan\vulkan.hpp>
#include <vector>

#include "Engine/Graphics/Mesh.hpp"

class ObjectBuffers
{
public:
	ObjectBuffers();
	~ObjectBuffers();

	std::vector<Engine::Vertex> vertices;
	vk::UniqueBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	std::vector<uint32_t> indices;
	vk::UniqueBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	vk::UniqueBuffer uniformBuffers;
	vk::DeviceMemory uniformBuffersMemory;
	void createVertexIndexUniformsBuffers(Engine::Mesh modelType);
	void destroy();
	void createUniformBuffers();
private:
	void createVertexBuffer();
	void createIndexBuffer();
};