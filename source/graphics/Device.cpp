#include "Device.hpp"

Device::Device(std::shared_ptr<Instance> gInstance)
{
    _physicalDevice = std::make_shared<vk::PhysicalDevice>(gInstance->getInstance()->get().enumeratePhysicalDevices().front());
    std::vector<vk::QueueFamilyProperties> queueFamilyProperties = _physicalDevice->getQueueFamilyProperties();
    graphicsQueueFamilyIndex = std::distance(
        queueFamilyProperties.begin(),
        std::find_if(
            queueFamilyProperties.begin(), queueFamilyProperties.end(), [](vk::QueueFamilyProperties const &qfp) {
                return qfp.queueFlags & vk::QueueFlagBits::eGraphics;
            }));
    assert(graphicsQueueFamilyIndex < queueFamilyProperties.size());

    _physicalDeviceFeatures = _physicalDevice->getFeatures();

    _commandPool = _uniqueDevice->get().createCommandPoolUnique(
        vk::CommandPoolCreateInfo(vk::CommandPoolCreateFlags(), graphicsQueueFamilyIndex));

    _commandBuffer = std::move(_uniqueDevice->get().allocateCommandBuffersUnique(vk::CommandBufferAllocateInfo(
                                                                                     _commandPool.get(), vk::CommandBufferLevel::ePrimary, 1))
                                   .front());
}

Device::~Device()
{
}

void Device::createUniqueDevice()
{
    std::vector<std::string> const extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    std::vector<char const *> enabledExtensions;
    enabledExtensions.reserve(extensions.size());
    for (auto const &ext : extensions)
    {
        enabledExtensions.push_back(ext.data());
    }

    float queuePriority = 0.0f;
    vk::DeviceQueueCreateInfo deviceQueueCreateInfo(
        vk::DeviceQueueCreateFlags(), graphicsQueueFamilyIndex, 1, &queuePriority);
    vk::DeviceCreateInfo deviceCreateInfo(
        vk::DeviceCreateFlags(), deviceQueueCreateInfo, {}, enabledExtensions, &_physicalDeviceFeatures);
    deviceCreateInfo.pNext = nullptr;
}

std::shared_ptr<vk::PhysicalDevice> Device::getPhysicalDevice()
{
    return _physicalDevice;
}

std::shared_ptr<vk::UniqueDevice> Device::getUniqueDevice()
{
    return _uniqueDevice;
}