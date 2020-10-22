#include "Engine/Resource/ResourceManager.hpp"

#include "Engine/Resource/MeshLoader.hpp"
#include "Engine/Resource/TextLoader.hpp"
#include "Engine/Resource/TextureLoader.hpp"

Engine::ResourceManager::ResourceManager()
{
    defaultInitialize();
}

Engine::ResourceManager::ResourceManager(bool allowDuplicates):
    _allowDuplicates(allowDuplicates)
{
    defaultInitialize();
}

void Engine::ResourceManager::init() noexcept
{
}

bool Engine::ResourceManager::registerResource(
    const std::string & name,
    ResourceType type,
    const std::filesystem::path & path
) noexcept {
    return registerResource({ type, name, path });
}

bool Engine::ResourceManager::registerResource(
    const ResourceDescriptor & descriptor
) noexcept {
    if (isResourceLoaded(descriptor.path)) {
        if (_allowDuplicates) {
            // TODO Log the duplicate ressource
        } else {
            // TODO Log the register attempt
            return false;
        }
    }
    if (isNameUsed(descriptor.name, descriptor.type)) {
        return false;
    }

    std::error_code code;

    if (!std::filesystem::exists(descriptor.path, code) || code) {
        return false;
    }
    _loadPendingResources.emplace(descriptor);
    return true;
}

void Engine::ResourceManager::unregisterResource(
    const std::string & name,
    ResourceType type
) noexcept {
    if (isNameUsed(name, type)) {
        _unloadPendingResources.push({ type, name });
    }
}

bool Engine::ResourceManager::loadResources() noexcept
{
    bool success = true;

    while (!_loadPendingResources.empty()) {
        const ResourceDescriptor & descriptor = _loadPendingResources.front();
        std::unique_ptr<Resource> resource = loadResource(descriptor);

        if (resource != nullptr) {
            _resources[descriptor.type][descriptor.name] = std::move(resource);
        } else {
            success = false;
        }
        _loadPendingResources.pop();
    }
    return success;
}

void Engine::ResourceManager::unloadResources() noexcept
{
    while (!_unloadPendingResources.empty()) {
        const ResourceDescriptor & descriptor = _unloadPendingResources.front();

        _resources[descriptor.type].erase(descriptor.name);
        _unloadPendingResources.pop();
    }
}

Engine::Resource * Engine::ResourceManager::getResource(
    const std::string & name,
    ResourceType type
) noexcept {
    auto pair = _resources[type].find(name);

    return (pair != _resources[type].end()) ? pair->second.get() : nullptr;
}

bool Engine::ResourceManager::isResourceLoaded(
    const std::filesystem::path & path
) const noexcept {
    return _loadedPathes.find(path) != _loadedPathes.end();
}

bool Engine::ResourceManager::isNameUsed(
    const std::string & name,
    ResourceType type
) const noexcept {
    return _resources[type].find(name) != _resources[type].end();
}

std::unique_ptr<Engine::Resource> Engine::ResourceManager::loadResource(const ResourceDescriptor & descriptor) const noexcept
{
    auto loader = _loaders[descriptor.type].find(descriptor.path.extension());

    if (loader != _loaders[descriptor.type].end()) {
        return loader->second(descriptor);
    } else {
        return nullptr;
    }
}

void Engine::ResourceManager::defaultInitialize() noexcept
{
    initializeLoaders();
    initializeResourceContainers();
}

void Engine::ResourceManager::initializeLoaders() noexcept
{
    _loaders[ResourceType::MeshType] = {
        { ".obj", loadMesh },
    };
    _loaders[ResourceType::TextureType] = {
        { ".png", loadTexture },
        { ".jpg", loadTexture },
    };
    _loaders[ResourceType::TextType] = {
        { ".txt", loadText },
    };
}

void Engine::ResourceManager::initializeResourceContainers() noexcept
{
    _resources = {
        ResourceContainer(),
        ResourceContainer(),
        ResourceContainer()
    };
}