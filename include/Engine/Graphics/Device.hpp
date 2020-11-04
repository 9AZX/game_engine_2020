#ifndef ENGINE_GRAPHICS_DEVICE_HPP_
#define ENGINE_GRAPHICS_DEVICE_HPP_

#include "Engine/Graphics/Instance.hpp"

#include <vulkan/vulkan.hpp>

namespace Engine {

class Device
{
public:
    Device(std::shared_ptr<Instance> gInstance);
    Device() = default;
    ~Device();

    std::shared_ptr<vk::PhysicalDevice> getPhysicalDevice();
    std::shared_ptr<vk::UniqueDevice> getUniqueDevice();

    void createUniqueDevice();

    size_t graphicsQueueFamilyIndex;

private:
    std::shared_ptr<vk::PhysicalDevice> _physicalDevice; // Physical device
    std::shared_ptr<vk::UniqueDevice> _uniqueDevice;     // Logical device

    vk::PhysicalDeviceFeatures _physicalDeviceFeatures;
    vk::UniqueCommandPool _commandPool;
    vk::UniqueCommandBuffer _commandBuffer;
}; /* class Device */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_DEVICE_HPP_ */
