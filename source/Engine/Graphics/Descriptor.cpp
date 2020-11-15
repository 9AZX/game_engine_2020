#include "Engine/Graphics/Descriptor.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/Graphics/UniformBufferObject.hpp"

#include <array>

void Engine::Descriptor::createDescriptorLayoutSetPoolAndAllocate(
    std::uint32_t swapchainImageCount
) {
    createDescriptorSetLayout();
    createDescriptorPoolAndAllocateSets(swapchainImageCount);
}

void Engine::Descriptor::populateDescriptorSets(
    std::uint32_t swapchainImageCount, vk::Buffer ubos
) {
    vk::Device device = Engine::Graphics::getInstance()->gDevice->getUniqueDevice()->get();

    for (std::size_t i = 0; i < swapchainImageCount; i++) {
        vk::DescriptorBufferInfo uboBufferDescInfo {};

        uboBufferDescInfo.buffer = ubos;
        uboBufferDescInfo.offset = 0;
        uboBufferDescInfo.range = sizeof(UniformBufferObject);

        vk::WriteDescriptorSet uboDescWrites;

        uboDescWrites.dstSet = descriptorSet;
        uboDescWrites.dstBinding = 0;
        uboDescWrites.dstArrayElement = 0;
        uboDescWrites.descriptorType = vk::DescriptorType::eUniformBuffer;
        uboDescWrites.descriptorCount = 1;
        uboDescWrites.pBufferInfo = &uboBufferDescInfo;

        std::array<vk::WriteDescriptorSet, 1> descWrites { uboDescWrites };

        device.updateDescriptorSets(
            static_cast<std::uint32_t>(descWrites.size()),
            descWrites.data(),
            0,
            nullptr
        );
    }
}

void Engine::Descriptor::createDescriptorSetLayout()
{
    vk::DescriptorSetLayoutBinding uboLayoutBinding {};

    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
    uboLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;

    std::array<vk::DescriptorSetLayoutBinding, 1> layoutBindings = { uboLayoutBinding };
    vk::DescriptorSetLayoutCreateInfo layoutCreateInfo {};

    layoutCreateInfo.setBindings(layoutBindings);

    vk::Device device = Engine::Graphics::getInstance()->gDevice->getUniqueDevice()->get();

    descriptorSetLayout = device.createDescriptorSetLayout(layoutCreateInfo);
}

void Engine::Descriptor::createDescriptorPoolAndAllocateSets(
    std::uint32_t swapchainImageCount
) {
    vk::Device device = Engine::Graphics::getInstance()->gDevice->getUniqueDevice()->get();
    std::array<vk::DescriptorPoolSize, 1> poolSizes {};

    poolSizes[0].type = vk::DescriptorType::eUniformBuffer;
    poolSizes[0].descriptorCount = swapchainImageCount;

    vk::DescriptorPoolCreateInfo poolCreateInfo {};

    poolCreateInfo.setPoolSizes(poolSizes);
    poolCreateInfo.maxSets = swapchainImageCount;

    descriptorPool = device.createDescriptorPool(poolCreateInfo);

    std::vector<vk::DescriptorSetLayout> layouts(swapchainImageCount, descriptorSetLayout);
    vk::DescriptorSetAllocateInfo allocateInfo;

    allocateInfo.descriptorPool = descriptorPool;
    allocateInfo.setSetLayouts(layouts);

    auto descriptorSetResult = device.allocateDescriptorSets(allocateInfo);

    descriptorSet = descriptorSetResult[0];
}

void Engine::Descriptor::destroy() {
    vk::Device device = Engine::Graphics::getInstance()->gDevice->getUniqueDevice()->get();

    device.destroyDescriptorPool(descriptorPool);
    device.destroyDescriptorSetLayout(descriptorSetLayout);
}
