#pragma once

#include <vulkan/vulkan.hpp>
#include "Engine/Maths/Vector3.hpp"
#include "Engine/Maths/Matrix4.hpp"
#include "Engine/Graphics/Descriptor.hpp"
#include "Engine/Graphics/ObjectBuffers.hpp"
#include "Engine/Graphics/Mesh.hpp"
#include "Engine/Graphics/Camera.hpp"
#include "Engine/Graphics/GraphicsPipeline.hpp"

class ObjectRenderer
{
public:

	void createObjectRenderer(Engine::Mesh modelType, Engine::Math::Vector3 _position, Engine::Math::Vector3 _scale);
	void draw();
	void updateUniformBuffer(Camera camera);
	void destroy();

private:


	Engine::GraphicsPipeline gPipeline;
	ObjectBuffers objBuffers;
	Engine::Descriptor descriptor;

	Engine::Math::Vector3 position;
	Engine::Math::Vector3 scale;

};
