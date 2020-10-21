#include "Engine/Resource/TextureLoader.hpp"

#include <iostream>

std::unique_ptr<Engine::Resource> Engine::loadTexture(const ResourceDescriptor & descriptor) noexcept
{
    std::cout << "Loading texture " << descriptor.name << " at " << descriptor.path << std::endl;
    return nullptr;
}
