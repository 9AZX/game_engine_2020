#include "Engine/Resources/Loaders/Texts/TextTxtLoader.hpp"

#include <iostream> // TODO remove include once logger is implemented

std::unique_ptr<Engine::Resource> Engine::TextTxtLoader::load(
    const ResourceDescriptor & descriptor
) noexcept {
    std::cout << "Loading tex at " << descriptor.path << std::endl;
    return nullptr;
}
