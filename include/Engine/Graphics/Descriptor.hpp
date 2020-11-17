#ifndef ENGINE_GRAPHICS_DESCRIPTOR_HPP_
#define ENGINE_GRAPHICS_DESCRIPTOR_HPP_

#include <cstdint>
#include <vulkan/vulkan.hpp>

#include "Engine/Graphics/Device.hpp"

namespace Engine {

class Descriptor {
    public:
        Descriptor(std::shared_ptr<Device> device) :_device(device)
        {

        }
        ~Descriptor() = default;

        vk::DescriptorSetLayout descriptorSetLayout;
        vk::DescriptorPool descriptorPool;
        vk::DescriptorSet descriptorSet;

        void createDescriptorLayoutSetPoolAndAllocate(
            std::uint32_t swapchainImageCount
        );

        void populateDescriptorSets(
            std::uint32_t swapchainImageCount, vk::Buffer ubos
        );

        void destroy();

    private:
        void createDescriptorSetLayout();
        void createDescriptorPoolAndAllocateSets(
            std::uint32_t swapchainImageCount
        );
        std::shared_ptr<Device> _device;
}; /* class Descriptor */

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_DESCRIPTOR_HPP_ */
