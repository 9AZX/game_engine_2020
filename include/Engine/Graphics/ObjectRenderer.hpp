#pragma once

#include <vulkan/vulkan.hpp>

class ObjectRenderer
{
public:

	void createObjectRenderer(MeshType modelType, glm::vec3 _position, glm::vec3 _scale);
	void draw();
	void updateUniformBuffer(Camera camera);
	void destroy();

	void createObjectRendererCPP(MeshType modelType, glm::vec3 _position, glm::vec3 _scale);
	void drawCPP();
	void updateUniformBufferCPP(Camera camera);

private:


	GraphicsPipeline gPipeline;
	ObjectBuffers objBuffers;
	Descriptor descriptor;

	glm::vec3 position;
	glm::vec3 scale;

};
