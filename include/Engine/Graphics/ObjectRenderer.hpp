#pragma once

#include <vulkan/vulkan.hpp>
#include "Engine/Maths/Vector3.hpp"
#include "Engine/Graphics/ObjectBuffers.hpp"

class ObjectRenderer
{
public:

	void createObjectRenderer(MeshType modelType, Engine::Math::Vector3 _position, Engine::Math::Vector3 _scale);
	void draw();
	void updateUniformBuffer(Camera camera);
	void destroy();

private:


	GraphicsPipeline gPipeline;
	ObjectBuffers objBuffers;
	Descriptor descriptor;

	Engine::Math::Vector3 position;
	Engine::Math::Vector3 scale;

};
