#ifndef INSTANCE_HPP_
#define INSTANCE_HPP_

#include <vulkan/vulkan.hpp>
class Instance
{
public:
    Instance(std::string);
    ~Instance();

    vk::UniqueInstance instance;

private:
    std::string _appName;

    vk::ApplicationInfo _applicationInfo;
    vk::InstanceCreateInfo _instanceCreateInfo;
};

#endif /* !INSTANCE_HPP_ */
