#include "Engine/Resources/Loaders/Shaders/SpirvShaderLoader.hpp"

#include "Engine/Resources/ShaderResource.hpp"

#include <fstream>

#include <iostream> // TODO Replace this once the logger is implemented

std::unique_ptr<Engine::Resource> Engine::SpirvShaderLoader::load(
    const ResourceDescriptor & descriptor
) noexcept {
    std::ifstream file(descriptor.path, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::cerr   << "[ShaderLoader][" << descriptor.path << "] "
                    << "Could not load file" << std::endl;
        return nullptr;
    }

    std::size_t fileSize = (std::size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return std::make_unique<ShaderResource>(
        descriptor.name,
        descriptor.path,
        std::move(buffer)
    );
}
