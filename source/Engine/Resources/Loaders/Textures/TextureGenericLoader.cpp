#include "Engine/Resources/Loaders/Textures/TextureGenericLoader.hpp"

#include <iostream> // TODO remove include once logger is implemented

std::unique_ptr<Engine::Resource> Engine::TextureGenericLoader::load(
    const ResourceDescriptor & descriptor
) noexcept {
    std::cout << "Loading texture at " << descriptor.path << std::endl;
    return nullptr;
}
