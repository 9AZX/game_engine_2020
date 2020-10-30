#include "graphics/Instance.hpp"

Instance::Instance(std::string appName) : _appName(appName)
{
    _applicationInfo = vk::ApplicationInfo(_appName.c_str(), 1, "3DGE", VK_API_VERSION_1_1);
    _instanceCreateInfo = vk::InstanceCreateInfo({}, &_applicationInfo);
    std::array<const char *, 2> extensions = {"VK_KHR_surface", "VK_KHR_win32_surface"};
    _instanceCreateInfo.setPEnabledExtensionNames(extensions);
    _instance = std::make_shared<vk::UniqueInstance>(vk::createInstanceUnique(_instanceCreateInfo));
}

Instance::~Instance()
{
}

std::shared_ptr<vk::UniqueInstance> Instance::getInstance()
{
    return _instance;
}