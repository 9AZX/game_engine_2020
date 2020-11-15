#ifndef ENGINE_GRAPHICS_DESCRIPTOR_HPP_
#define ENGINE_GRAPHICS_DESCRIPTOR_HPP_

#include <cstdint>
#include <vulkan/vulkan.hpp>

namespace Engine {

class Descriptor {
    public:
        Descriptor() = default;
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
}; /* class Descriptor */

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_DESCRIPTOR_HPP_ */
