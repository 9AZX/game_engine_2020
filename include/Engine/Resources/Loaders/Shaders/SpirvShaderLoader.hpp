#ifndef ENGINE_RESOURCES_LOADERS_SHADERS_SPIRV_SHADER_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_SHADERS_SPIRV_SHADER_LOADER_HPP_

#include "Engine/Resources/IResourceLoader.hpp"

namespace Engine {

class SpirvShaderLoader: public IResourceLoader {
    public:
        std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept override;
}; /* class SpirvShaderLoader */

} /* namespace Engine */


#endif /* ENGINE_RESOURCES_LOADERS_SHADERS_SPIRV_SHADER_LOADER_HPP_ */
