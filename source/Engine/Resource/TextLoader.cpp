#include "Engine/Resource/TextLoader.hpp"

#include <iostream>

std::unique_ptr<Engine::Resource> Engine::loadText(const ResourceDescriptor & descriptor) noexcept
{
    std::cout << "Loading text " << descriptor.name << " at " << descriptor.path << std::endl;
    return nullptr;
}
