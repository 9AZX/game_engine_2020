#include "Device.hpp"

Device::Device(std::shared_ptr<Instance> gInstance)
{
    _physicalDevice = std::make_shared<vk::PhysicalDevice>(gInstance->getInstance()->get().enumeratePhysicalDevices().front());
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = _physicalDevice->getQueueFamilyProperties();
    size_t graphicsQueueFamilyIndex = std::distance(
        queueFamilyProperties.begin(),
        std::find_if(
            queueFamilyProperties.begin(), queueFamilyProperties.end(), [](vk::QueueFamilyProperties const &qfp) {
                return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
            }));
    assert(graphicsQueueFamilyIndex < queueFamilyProperties.size());

    float queuePriority = 0.0f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo(
        vk::DeviceQueueCreateFlags(), static_cast<uint32_t>(graphicsQueueFamilyIndex), 1, &queuePriority);

    _uniqueDevice =
        std::make_shared<vk::UniqueDevice>(_physicalDevice->createDeviceUnique(vk::DeviceCreateInfo(vk::DeviceCreateFlags(), deviceQueueCreateInfo)));
}

Device::~Device()
{
}

std::shared_ptr<vk::PhysicalDevice> Device::getPhysicalDevice()
{
    return _physicalDevice;
}

std::shared_ptr<vk::UniqueDevice> Device::getUniqueDevice()
{
    return _uniqueDevice;
}