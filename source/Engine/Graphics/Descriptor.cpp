#include "Engine/Graphics/Descriptor.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/Graphics/UniformBufferObject.hpp"

#include <array>
#include <numeric>

void Engine::Descriptor::createDescriptorLayoutSetPoolAndAllocate(
    std::uint32_t swapchainImageCount
)
{
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

    //vk::Device device = Engine::Graphics::getInstance()->gDevice->getUniqueDevice()->get();

    descriptorSetLayout = _device->getUniqueDevice()->get().createDescriptorSetLayout(layoutCreateInfo);
}

void Engine::Descriptor::createDescriptorPoolAndAllocateSets(
    std::uint32_t swapchainImageCount
) {
    //vk::Device device = _device->getUniqueDevice()->get();
    //std::array<vk::DescriptorPoolSize, 1> poolSizes {};
    std::vector<vk::DescriptorPoolSize> const& poolSizes = { { vk::DescriptorType::eUniformBuffer, 1 } };
    /*poolSizes[0].type = vk::DescriptorType::eUniformBuffer;
    poolSizes[0].descriptorCount = swapchainImageCount;*/
    uint32_t maxSets =
        std::accumulate(poolSizes.begin(), poolSizes.end(), 0, [](uint32_t sum, vk::DescriptorPoolSize const& dps) {
        return sum + dps.descriptorCount;
            });
    //vk::DescriptorPoolCreateInfo poolCreateInfo {};

    //poolCreateInfo.setPoolSizes(poolSizes);
    ////poolCreateInfo.sType = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;
    //poolCreateInfo.maxSets = swapchainImageCount;
    //poolCreateInfo.pPoolSizes = poolSizes.data();
    //poolCreateInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());

    vk::DescriptorPoolCreateInfo poolCreateInfo(
        vk::DescriptorPoolCreateFlags(), maxSets, poolSizes);

    descriptorPool = _device->getUniqueDevice()->get().createDescriptorPool(poolCreateInfo);

    std::vector<vk::DescriptorSetLayout> layouts(maxSets, descriptorSetLayout);
    vk::DescriptorSetAllocateInfo allocateInfo;

    allocateInfo.descriptorPool = descriptorPool;
    allocateInfo.setSetLayouts(layouts);

    auto descriptorSetResult = _device->getUniqueDevice()->get().allocateDescriptorSets(allocateInfo);

    descriptorSet = descriptorSetResult[0];
}

void Engine::Descriptor::destroy() {
    vk::Device device = Engine::Graphics::getInstance()->gDevice->getUniqueDevice()->get();

    device.destroyDescriptorPool(descriptorPool);
    device.destroyDescriptorSetLayout(descriptorSetLayout);
}
