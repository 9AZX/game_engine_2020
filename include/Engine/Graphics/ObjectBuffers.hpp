#include <vulkan\vulkan.hpp>
#include <vector>

#include "Mesh.h"

class ObjectBuffers
{
public:
	ObjectBuffers();
	~ObjectBuffers();

	std::vector<Vertex> vertices;
	vk::UniqueBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	std::vector<uint32_t> indices;
	vk::UniqueBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	vk::UniqueBuffer uniformBuffers;
	vk::DeviceMemory uniformBuffersMemory;
	void createVertexIndexUniformsBuffers(MeshType modelType);
	void destroy();
private:
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();
};