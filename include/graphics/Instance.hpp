#ifndef INSTANCE_HPP_
#define INSTANCE_HPP_

#include <vulkan/vulkan.hpp>

class Instance
{
public:
    Instance(std::string);
    ~Instance();

private:
    std::string _appName;

    vk::ApplicationInfo _applicationInfo;
    vk::InstanceCreateInfo _instanceCreateInfo;
    vk::UniqueInstance _instance;
};

#endif /* !INSTANCE_HPP_ */
