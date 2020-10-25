#ifndef ENGINE_RESOURCES_LOADERS_TEXTURES_TEXTURE_GENERIC_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_TEXTURES_TEXTURE_GENERIC_LOADER_HPP_

#include "Engine/Resources/IResourceLoader.hpp"

namespace Engine {

class TextureGenericLoader: public IResourceLoader {
    public:
        std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept override;
}; /* class TextureGenericLoader */

} /* namespace Engine */


#endif /* ENGINE_RESOURCES_LOADERS_TEXTURES_TEXTURE_GENERIC_LOADER_HPP_ */
