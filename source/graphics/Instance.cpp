#include "graphics/Instance.hpp"

Instance::Instance(std::string appName) : _appName(appName)
{
    _applicationInfo = vk::ApplicationInfo(_appName.c_str(), 1, "3DGE", VK_API_VERSION_1_1);
    _instanceCreateInfo = vk::InstanceCreateInfo({}, &_applicationInfo);
    _instance = vk::createInstanceUnique(_instanceCreateInfo);
}

Instance::~Instance()
{
}

vk::UniqueInstance *Instance::getInstance()
{
    return &_instance;
}