#ifndef ENGINE_RESOURCES_LOADERS_SHADERS_SPIRV_SHADER_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_SHADERS_SPIRV_SHADER_LOADER_HPP_

#include "Engine/Logging/Logger.hpp"
#include "Engine/Resources/IResourceLoader.hpp"

#include <memory>

namespace Engine {

class SpirvShaderLoader: public IResourceLoader {
    public:
        SpirvShaderLoader(std::shared_ptr<Logging::Logger> logger);

        std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept override;

    private:
        std::shared_ptr<Logging::Logger> _logger;
}; /* class SpirvShaderLoader */

} /* namespace Engine */


#endif /* ENGINE_RESOURCES_LOADERS_SHADERS_SPIRV_SHADER_LOADER_HPP_ */
