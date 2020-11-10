#ifndef ENGINE_RESOURCES_I_RESOURCE_LOADER_HPP_
#define ENGINE_RESOURCES_I_RESOURCE_LOADER_HPP_

#include "Engine/Resources/Resource.hpp"
#include "Engine/Resources/ResourceDescriptor.hpp"

#include <memory>

namespace Engine {

class IResourceLoader {
    public:
        virtual ~IResourceLoader() = default;

        virtual std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept = 0;
}; /* class IResourceLoader */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_I_RESOURCE_LOADER_HPP_ */
