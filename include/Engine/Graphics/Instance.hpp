#ifndef ENGINE_GRAPHICS_INSTANCE_HPP_
#define ENGINE_GRAPHICS_INSTANCE_HPP_

#include <memory>
#include <string>
#include <vector>

#include <vulkan/vulkan.hpp>

namespace Engine {

class Instance
{
public:
    Instance(std::string appName, bool enableDebugging);
    Instance() = default;
    ~Instance();

    std::shared_ptr<vk::UniqueInstance> getInstance();

private:
    std::vector<const char *> getExtensions(bool enableDebugging);
    std::vector<const char *> getLayers(bool enableDebugging);
    bool checkLayerSupport(std::vector<const char *> layers);

    std::string _appName;
    bool _enableDebugging;
    std::shared_ptr<vk::UniqueInstance> _instance;

    vk::ApplicationInfo _applicationInfo;
    vk::InstanceCreateInfo _instanceCreateInfo;

    static std::vector<const char *> _instanceExtensions;;
    static std::vector<const char *> _debugExtensions;
    static std::vector<const char *> _validationLayers;
}; /* class Instance */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_INSTANCE_HPP_ */
