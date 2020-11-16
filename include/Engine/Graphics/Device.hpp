#ifndef ENGINE_GRAPHICS_DEVICE_HPP_
#define ENGINE_GRAPHICS_DEVICE_HPP_

#include "Engine/Graphics/Instance.hpp"

#include <vulkan/vulkan.hpp>

namespace Engine {

    struct QueueFamilyIndices {
        int graphicsFamily = -1;
        int presentFamily = -1;
        bool arePresent() {
            return graphicsFamily >= 0 && presentFamily >= 0;
        }
    };


class Device
{
public:
    Device(std::shared_ptr<Instance> gInstance);
    Device() = default;
    ~Device();

    std::shared_ptr<vk::PhysicalDevice> getPhysicalDevice();
    std::shared_ptr<vk::UniqueDevice> getUniqueDevice();

    void createUniqueDevice();

    QueueFamilyIndices Device::getQueueFamiliesIndicesOfCurrentDevice()
    {
        return queueFamiliyIndices;
    }

    size_t getGraphicsQueueFamilyIndex();

    vk::Queue graphicsQueue;
    vk::Queue presentQueue;
    size_t graphicsQueueFamilyIndex;
private:
    QueueFamilyIndices queueFamiliyIndices;
    std::shared_ptr<vk::PhysicalDevice> _physicalDevice; // Physical device
    std::shared_ptr<vk::UniqueDevice> _uniqueDevice;     // Logical device

    vk::PhysicalDeviceFeatures _physicalDeviceFeatures;
    vk::UniqueCommandPool _commandPool;
    vk::UniqueCommandBuffer _commandBuffer;


    
}; /* class Device */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_DEVICE_HPP_ */
