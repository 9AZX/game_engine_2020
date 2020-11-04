#ifndef ENGINE_GRAPHICS_INSTANCE_HPP_
#define ENGINE_GRAPHICS_INSTANCE_HPP_

#include <vulkan/vulkan.hpp>

namespace Engine {

class Instance
{
public:
    Instance(std::string);
    Instance() = default;
    ~Instance();

    std::shared_ptr<vk::UniqueInstance> getInstance();

private:
    std::string _appName;
    std::shared_ptr<vk::UniqueInstance> _instance;

    vk::ApplicationInfo _applicationInfo;
    vk::InstanceCreateInfo _instanceCreateInfo;
}; /* class Instance */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_INSTANCE_HPP_ */
