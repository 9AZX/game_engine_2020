#include "Engine/Graphics/ObjectRenderer.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/Graphics/Descriptor.hpp"

struct UniformBufferObject
{
	Engine::Math::Matrix4 model;
	Engine::Math::Matrix4 view;
	Engine::Math::Matrix4 proj;
};

void ObjectRenderer::createObjectRenderer(Engine::Mesh modelType, Engine::Math::Vector3 _position, Engine::Math::Vector3 _scale)
{
	uint32_t swapChainImageCount = Engine::Graphics::getInstance()->getSwapchain()->swapChainImages.size();
	vk::Extent2D swapChainImageExtent = Engine::Graphics::getInstance()->getSwapchain()->swapChainImageExtent;

	objBuffers.createVertexIndexUniformsBuffers(modelType);

	descriptor.createDescriptorLayoutSetPoolAndAllocate(swapChainImageCount);
	descriptor.populateDescriptorSets(swapChainImageCount,
									  objBuffers.uniformBuffers.get());

	// Here register the object vertex or create pipeline or find a solution

	position = _position;
	scale = _scale;
}

void ObjectRenderer::draw()
{
	vk::UniqueCommandBuffer cBuffer = Engine::Graphics::getInstance()->currentCommandBuffer;
	cBuffer->bindPipeline(vk::PipelineBindPoint::eGraphics, gPipeline._graphicsPipeline.get());

	vk::Buffer vertexBuffers[] = {objBuffers.vertexBuffer.get()};
	vk::DeviceSize offsets[] = {0};

	cBuffer->bindVertexBuffers(0, 1, vertexBuffers, offsets);
	cBuffer->bindIndexBuffer(objBuffers.indexBuffer.get(),
							 0,
							 vk::IndexType::eUint32);

	cBuffer->bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
								gPipeline._pipelineLayout.get(),
								0,
								1,
								&descriptor.descriptorSet, 0, nullptr);
	cBuffer->drawIndexed(static_cast<uint32_t>(objBuffers.indices.size()),
						 1,
						 0,
						 0,
						 0);
}

Engine::Math::Matrix4 ourScale(Engine::Math::Matrix4 matrix, Engine::Math::Vector3 vector)
{
	Engine::Math::Matrix4 Result;

	Result.matrixData[0] = matrix.matrixData[0] * vector.x;
	Result.matrixData[1] = matrix.matrixData[1] * vector.x;
	Result.matrixData[2] = matrix.matrixData[2] * vector.x;
	Result.matrixData[3] = matrix.matrixData[3] * vector.x;

	Result.matrixData[4] = matrix.matrixData[4] * vector.y;
	Result.matrixData[5] = matrix.matrixData[5] * vector.y;
	Result.matrixData[6] = matrix.matrixData[6] * vector.y;
	Result.matrixData[7] = matrix.matrixData[7] * vector.y;

	Result.matrixData[8] = matrix.matrixData[8] * vector.z;
	Result.matrixData[9] = matrix.matrixData[9] * vector.z;
	Result.matrixData[10] = matrix.matrixData[10] * vector.z;
	Result.matrixData[11] = matrix.matrixData[11] * vector.z;

	Result.matrixData[12] = matrix.matrixData[12];
	Result.matrixData[13] = matrix.matrixData[13];
	Result.matrixData[14] = matrix.matrixData[14];
	Result.matrixData[15] = matrix.matrixData[15];

	return Result;
}

Engine::Math::Matrix4 ourTranslate(Engine::Math::Matrix4 matrix, Engine::Math::Vector3 vector)
{
	Engine::Math::Matrix4 Result(matrix);

	Result.matrixData[12] = matrix.matrixData[0] * vector.x + matrix.matrixData[1] * vector.x + matrix.matrixData[2] * vector.x + matrix.matrixData[3] * vector.x + matrix.matrixData[4] * vector.y + matrix.matrixData[5] * vector.y + matrix.matrixData[6] * vector.y + matrix.matrixData[7] * vector.y + matrix.matrixData[8] * vector.z + matrix.matrixData[9] * vector.z + matrix.matrixData[10] * vector.z + matrix.matrixData[11] * vector.z + matrix.matrixData[12] + matrix.matrixData[13] + matrix.matrixData[14] + matrix.matrixData[15];

	Result.matrixData[13] = matrix.matrixData[0] * vector.x + matrix.matrixData[1] * vector.x + matrix.matrixData[2] * vector.x + matrix.matrixData[3] * vector.x + matrix.matrixData[4] * vector.y + matrix.matrixData[5] * vector.y + matrix.matrixData[6] * vector.y + matrix.matrixData[7] * vector.y + matrix.matrixData[8] * vector.z + matrix.matrixData[9] * vector.z + matrix.matrixData[10] * vector.z + matrix.matrixData[11] * vector.z + matrix.matrixData[12] + matrix.matrixData[13] + matrix.matrixData[14] + matrix.matrixData[15];

	Result.matrixData[14] = matrix.matrixData[0] * vector.x + matrix.matrixData[1] * vector.x + matrix.matrixData[2] * vector.x + matrix.matrixData[3] * vector.x + matrix.matrixData[4] * vector.y + matrix.matrixData[5] * vector.y + matrix.matrixData[6] * vector.y + matrix.matrixData[7] * vector.y + matrix.matrixData[8] * vector.z + matrix.matrixData[9] * vector.z + matrix.matrixData[10] * vector.z + matrix.matrixData[11] * vector.z + matrix.matrixData[12] + matrix.matrixData[13] + matrix.matrixData[14] + matrix.matrixData[15];

	Result.matrixData[15] = matrix.matrixData[0] * vector.x + matrix.matrixData[1] * vector.x + matrix.matrixData[2] * vector.x + matrix.matrixData[3] * vector.x + matrix.matrixData[4] * vector.y + matrix.matrixData[5] * vector.y + matrix.matrixData[6] * vector.y + matrix.matrixData[7] * vector.y + matrix.matrixData[8] * vector.z + matrix.matrixData[9] * vector.z + matrix.matrixData[10] * vector.z + matrix.matrixData[11] * vector.z + matrix.matrixData[12] + matrix.matrixData[13] + matrix.matrixData[14] + matrix.matrixData[15];
}

void ObjectRenderer::updateUniformBuffer(Camera camera)
{
	UniformBufferObject ubo = {};

	Engine::Math::Matrix4 scaleMatrix = Engine::Math::Matrix4(1.0f);
	Engine::Math::Matrix4 rotMatrix = Engine::Math::Matrix4(1.0f);
	Engine::Math::Matrix4 transMatrix = Engine::Math::Matrix4(1.0f);

	scaleMatrix = ourScale(Engine::Math::Matrix4(1.0f), scale);
	transMatrix = ourTranslate(Engine::Math::Matrix4(1.0f), position);

	ubo.model = transMatrix * rotMatrix * scaleMatrix;

	ubo.view = camera.getViewMatrix();

	ubo.proj = camera.getprojectionMatrix();

	ubo.proj.matrixData[5] *= -1;

	void *data;

	data = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().mapMemory(objBuffers.uniformBuffersMemory, 0, sizeof(ubo));

	memcpy(data, &ubo, sizeof(ubo));
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().unmapMemory(objBuffers.uniformBuffersMemory);
}

void ObjectRenderer::destroy()
{

	//gPipeline.destroy();
	descriptor.destroy();
	objBuffers.destroy();
}
