#ifndef ENGINE_RESOURCE_RESOURCE_DESCRIPTOR_HPP_
#define ENGINE_RESOURCE_RESOURCE_DESCRIPTOR_HPP_

#include "Engine/Resource/ResourceType.hpp"

#include <filesystem>
#include <string>

namespace Engine {

struct ResourceDescriptor {
    ResourceType type;
    std::string name;
    std::filesystem::path path;
}; /* struct ResourceDescriptor */

} /* namespace Engine */

#endif /* ENGINE_RESOURCE_RESOURCE_DESCRIPTOR_HPP_ */