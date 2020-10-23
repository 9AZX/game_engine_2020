#include "Device.hpp"

Device::Device(std::shared_ptr<Instance> gInstance)
{
    _physicalDevice = gInstance->getInstance()->get().enumeratePhysicalDevices().front();
}

Device::~Device()
{
}

std::shared_ptr<vk::PhysicalDevice> Device::getPhysicalDevice()
{
    return std::make_shared<vk::PhysicalDevice>(_physicalDevice);
}