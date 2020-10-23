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

private:
    vk::PhysicalDevice _physicalDevice;
};

#endif /* !DEVICE_HPP_ */
