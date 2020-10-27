#include "Device.hpp"

Device::Device(std::shared_ptr<Instance> gInstance)
{
    _physicalDevice = std::make_shared<vk::PhysicalDevice>(gInstance->getInstance()->get().enumeratePhysicalDevices().front());
}

Device::~Device()
{
}

std::shared_ptr<vk::PhysicalDevice> Device::getPhysicalDevice()
{
    return _physicalDevice;
}