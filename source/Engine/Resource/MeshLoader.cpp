#include "Engine/Resource/MeshLoader.hpp"

#include <iostream>

std::unique_ptr<Engine::Resource> Engine::loadMesh(const ResourceDescriptor & descriptor) noexcept
{
    std::cout << "Loading mesh " << descriptor.name << " at " << descriptor.path << std::endl;
    return nullptr;
}
