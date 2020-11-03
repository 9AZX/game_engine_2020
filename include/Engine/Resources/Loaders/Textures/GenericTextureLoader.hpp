#ifndef ENGINE_RESOURCES_LOADERS_TEXTURES_GENERIC_TEXTURE_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_TEXTURES_GENERIC_TEXTURE_LOADER_HPP_

#include "Engine/Resources/IResourceLoader.hpp"

namespace Engine {

class GenericTextureLoader: public IResourceLoader {
    public:
        std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept override;
}; /* class GenericTextureLoader */

} /* namespace Engine */


#endif /* ENGINE_RESOURCES_LOADERS_TEXTURES_GENERIC_TEXTURE_LOADER_HPP_ */
