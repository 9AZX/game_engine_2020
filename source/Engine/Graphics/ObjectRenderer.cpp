#include "Engine/Graphics/ObjectRenderer.hpp"
#include "Engine/Graphics.hpp"

void ObjectRenderer::createObjectRenderer(MeshType modelType, glm::vec3 _position, glm::vec3 _scale) {


	uint32_t swapChainImageCount = Engine::Graphics::getInstance()->getSwapchain()->swapChainImages.size();
	VkExtent2D swapChainImageExtent = Engine::Graphics::getInstance()->getSwapchain()->swapChainImageExtent;



	// Create Vertex, Index and Uniforms Buffer;
	objBuffers.createVertexIndexUniformsBuffers(modelType);

	// CreateDescriptorSetLayout
	descriptor.createDescriptorLayoutSetPoolAndAllocate(swapChainImageCount);
	descriptor.populateDescriptorSets(swapChainImageCount,
		objBuffers.uniformBuffers);

	// CreateGraphicsPipeline
	gPipeline.createGraphicsPipelineLayoutAndPipeline(
		swapChainImageExtent,
		descriptor.descriptorSetLayout,
		Engine::Graphics::getInstance()->getRenderpass()->renderPass);


	position = _position;
	scale = _scale;
}

void ObjectRenderer::createObjectRenderer(MeshType modelType, glm::vec3 _position, glm::vec3 _scale)
{
	uint32_t swapChainImageCount = Engine::Graphics::getInstance()->getSwapchain()->swapChainImages.size();
	vk::Extent2D swapChainImageExtent = Engine::Graphics::getInstance()->getSwapchain()->swapChainImageExtent;

	objBuffers.createVertexIndexUniformsBuffers(modelType);

	descriptor.createDescriptorLayoutSetPoolAndAllocate(swapChainImageCount);
	descriptor.populateDescriptorSets(swapChainImageCount,
		objBuffers.uniformBuffers);

	// CreateGraphicsPipeline
	gPipeline.createGraphicsPipelineLayoutAndPipeline(
		swapChainImageExtent,
		descriptor.descriptorSetLayout,
		Engine::Graphics::getInstance()->getRenderpass()->renderPass);


	position = _position;
	scale = _scale;
}

void ObjectRenderer::draw()
{
	vk::UniqueCommandBuffer cBuffer = Engine::Graphics::getInstance()->getCurrentCommandBuffer();
	cBuffer->bindPipeline(vk::PipelineBindPoint::eGraphics, gPipeline.graphicsPipeline);

	vk::Buffer vertexBuffers[] = { objBuffers.vertexBuffer };
	vk::DeviceSize offsets[] = { 0 };

	cBuffer->bindVertexBuffers(0, 1, vertexBuffers, offsets);
	cBuffer->bindIndexBuffer(objBuffers.indexBuffer,
		0,
		vk::IndexType::eUint32);

	cBuffer->bindDescriptorSets(vk::PipelineBindPoint::eGraphics,
		gPipeline.pipelineLayout,
		0,
		1,
		&descriptor.descriptorSet, 0, nullptr);
	cBuffer->drawIndexed(static_cast<uint32_t>(objBuffers.indices.size()),
		1, 
		0, 
		0, 
		0);
}

void ObjectRenderer::updateUniformBuffer(Camera camera)
{
	UniformBufferObject ubo = {};

	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 rotMatrix = glm::mat4(1.0f);
	glm::mat4 transMatrix = glm::mat4(1.0f);

	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	transMatrix = glm::translate(glm::mat4(1.0f), position);

	ubo.model = transMatrix * rotMatrix * scaleMatrix;

	ubo.view = camera.getViewMatrix();

	ubo.proj = camera.getprojectionMatrix();

	ubo.proj[1][1] *= -1;

	void* data;

	data = Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().mapMemory(objBuffers.uniformBuffersMemory, 0, sizeof(ubo));
	
	memcpy(data, &ubo, sizeof(ubo));
	Engine::Graphics::getInstance()->getDevice()->getUniqueDevice()->get().unmapMemory(objBuffers.uniformBuffersMemory);
}

void ObjectRenderer::destroy() {

	gPipeline.destroy();
	descriptor.destroy();
	objBuffers.destroy();
}
