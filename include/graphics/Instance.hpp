#ifndef INSTANCE_HPP_
#define INSTANCE_HPP_

#include <vulkan/vulkan.hpp>
class Instance
{
public:
    Instance(std::string);
    ~Instance();

    std::shared_ptr<vk::UniqueInstance> getInstance();

private:
    std::string _appName;
    vk::UniqueInstance _instance;

    vk::ApplicationInfo _applicationInfo;
    vk::InstanceCreateInfo _instanceCreateInfo;
};

#endif /* !INSTANCE_HPP_ */
