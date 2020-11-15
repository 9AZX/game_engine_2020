#include "Engine/Graphics/Instance.hpp"

#include <cstring>

std::vector<const char *> Engine::Instance::_instanceExtensions {
    "VK_KHR_surface",
    "VK_KHR_win32_surface"
};

std::vector<const char *> Engine::Instance::_debugExtensions {
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME
};

std::vector<const char *> Engine::Instance::_validationLayers {
    "VK_LAYER_KHRONOS_validation"
};

Engine::Instance::Instance(std::string appName, bool enableDebugging):
    _appName(appName),
    _enableDebugging(enableDebugging)
{
    std::vector<const char *> layers
        = getLayers(enableDebugging);
    std::vector<const char *> extensions
        = getExtensions(enableDebugging);

    _applicationInfo = vk::ApplicationInfo(
        _appName.c_str(), 1, "3DGE",
        VK_API_VERSION_1_1
    );
    _instanceCreateInfo.setPApplicationInfo(&_applicationInfo);
    _instanceCreateInfo.setPEnabledLayerNames(layers);
    _instanceCreateInfo.setPEnabledExtensionNames(extensions);
    _instance = std::make_shared<vk::UniqueInstance>(
        vk::createInstanceUnique(_instanceCreateInfo)
    );
}

Engine::Instance::~Instance()
{
}

std::shared_ptr<vk::UniqueInstance> Engine::Instance::getInstance()
{
    return _instance;
}

std::vector<const char *> Engine::Instance::getExtensions(bool enableDebugging)
{
    std::vector<const char *> extensions = _instanceExtensions;

    if (enableDebugging) {
        extensions.insert(
            extensions.end(),
            _debugExtensions.begin(),
            _debugExtensions.end()
        );
    }
    return extensions;
}

std::vector<const char *> Engine::Instance::getLayers(
    bool enableDebugging
) {
    std::vector<const char *> instanceLayers {};

    if (enableDebugging && checkLayerSupport(_validationLayers)) {
        instanceLayers.insert(
            instanceLayers.end(),
            _validationLayers.begin(),
            _validationLayers.end()
        );
    }
    return instanceLayers;
}

bool Engine::Instance::checkLayerSupport(
    std::vector<const char *> layers
) {
    std::vector<vk::LayerProperties> availableLayers
        = vk::enumerateInstanceLayerProperties();

    for (const char * layerName: layers) {
        bool available = false;

        for (const auto & properties: availableLayers) {
            if (std::strcmp(layerName, properties.layerName) == 0) {
                available = true;
                break;
            }
        }
        if (!available) {
            return false;
        }
    }
    return true;
}
