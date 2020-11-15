#include "Engine/Resources/Loaders/Shaders/SpirvShaderLoader.hpp"

#include "Engine/Resources/ShaderResource.hpp"

#include <fstream>

Engine::SpirvShaderLoader::SpirvShaderLoader(
    std::shared_ptr<Logging::Logger> logger
):
    _logger(logger)
{
}

std::unique_ptr<Engine::Resource> Engine::SpirvShaderLoader::load(
    const ResourceDescriptor & descriptor
) noexcept {
    std::ifstream file(descriptor.path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        _logger->log(
            Logging::Level::Error,
            "[Shader Loader] {}: could not load file",
            descriptor.path.string()
        );
        return nullptr;
    }

    std::size_t fileSize = static_cast<std::size_t>(file.tellg());
    std::size_t bufferSize = static_cast<std::size_t>(
        std::floor(fileSize / sizeof(unsigned int))
    );
    std::vector<unsigned int> buffer(bufferSize);

    file.seekg(0);
    file.read(reinterpret_cast<char *>(buffer.data()), fileSize);
    file.close();

    return std::make_unique<ShaderResource>(
        descriptor.name,
        descriptor.path,
        std::move(buffer)
    );
}
