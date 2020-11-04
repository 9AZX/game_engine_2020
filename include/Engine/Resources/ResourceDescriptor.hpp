#ifndef ENGINE_RESOURCES_RESOURCE_DESCRIPTOR_HPP_
#define ENGINE_RESOURCES_RESOURCE_DESCRIPTOR_HPP_

#include "Engine/Resources/ResourceType.hpp"

#include <filesystem>
#include <string>

namespace Engine {

struct ResourceDescriptor {
    ResourceType type;
    std::string name;
    std::filesystem::path path;
}; /* struct ResourceDescriptor */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_RESOURCE_DESCRIPTOR_HPP_ */