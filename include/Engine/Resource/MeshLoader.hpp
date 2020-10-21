#ifndef ENGINE_RESOURCE_MESH_LOADER_HPP_
#define ENGINE_RESOURCE_MESH_LOADER_HPP_

#include "Engine/Resource/Resource.hpp"
#include "Engine/Resource/ResourceDescriptor.hpp"

#include <memory>

namespace Engine {

std::unique_ptr<Resource> loadMesh(const ResourceDescriptor & descriptor) noexcept;

} /* namespace Engine */

#endif /* ENGINE_RESOURCE_MESH_LOADER_HPP_ */
