#ifndef DEVICE_HPP_
#define DEVICE_HPP_

#include <vulkan/vulkan.hpp>
#include "graphics/Instance.hpp"

class Device
{
public:
    Device(std::shared_ptr<Instance> gInstance);
    Device() = default;
    ~Device();

    std::shared_ptr<vk::PhysicalDevice> getPhysicalDevice();
    std::shared_ptr<vk::UniqueDevice> getUniqueDevice();

private:
    std::shared_ptr<vk::PhysicalDevice> _physicalDevice;
    std::shared_ptr<vk::UniqueDevice> _uniqueDevice;
};

#endif /* !DEVICE_HPP_ */
