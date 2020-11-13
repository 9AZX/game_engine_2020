#include "Engine/Resources/ResourceManager.hpp"

#include "Engine/Resources/Loaders/Textures/GenericTextureLoader.hpp"
#include "Engine/Resources/Loaders/Meshes/ObjMeshLoader.hpp"
#include "Engine/Resources/Loaders/Shaders/SpirvShaderLoader.hpp"
#include "Engine/Resources/Loaders/Texts/TextTxtLoader.hpp"

#include <algorithm>

Engine::ResourceManager::ResourceManager(
    std::shared_ptr<Logging::Logger> logger,
    bool allowDuplicates
):
    _logger(logger),
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
            _logger->log(
                Logging::Level::Warning,
                "[Resource Manager] Loading {} as {} but already loaded"
                " as another resource",
                descriptor.path.string(),
                descriptor.name
            );
        } else {
            _logger->log(
                Logging::Level::Error,
                "[Resource Manager] Refusing to load {} a second time",
                descriptor.path.string(),
                descriptor.name
            );
            return false;
        }
    }
    if (isNameUsed(descriptor.name, descriptor.type)) {
        _logger->log(
            Logging::Level::Error,
            "[Resource Manager] Tried to load {} as {} but the name"
            " is alreay used",
            descriptor.path.string(),
            descriptor.name
        );
        return false;
    }

    std::error_code code;

    if (!std::filesystem::exists(descriptor.path, code) || code) {
        _logger->log(
            Logging::Level::Error,
            "[Resource Manager] {} does not exist",
            descriptor.path.string()
        );
        return false;
    }
    _loadPendingResources.emplace_back(descriptor);
    return true;
}

void Engine::ResourceManager::unregisterResource(
    const std::string & name,
    ResourceType type
) noexcept {
    if (isNameUsed(name, type)) {
        _logger->log(
            Logging::Level::Warning,
            "[Resource Manager] Trying to unload an unknown resource: {}",
            name
        );
        _unloadPendingResources.push_back({ type, name });
    }
}

bool Engine::ResourceManager::loadResources() noexcept
{
    bool success = true;

    while (!_loadPendingResources.empty()) {
        const ResourceDescriptor & descriptor = _loadPendingResources.front();
        std::unique_ptr<Resource> resource = loadResource(descriptor);

        if (resource != nullptr) {
            _logger->log(
                Logging::Level::Error,
                "[Resource Manager] Successfully loaded {} as {}",
                descriptor.path.string(),
                descriptor.name
            );
            _resources[descriptor.type][descriptor.name] = std::move(resource);
        } else {
            _logger->log(
                Logging::Level::Error,
                "[Resource Manager] Could not load {} as {}",
                descriptor.path.string(),
                descriptor.name
            );
            success = false;
        }
        _loadPendingResources.pop_front();
    }
    return success;
}

void Engine::ResourceManager::unloadResources() noexcept
{
    while (!_unloadPendingResources.empty()) {
        const ResourceDescriptor & descriptor = _unloadPendingResources.front();

        _resources[descriptor.type].erase(descriptor.name);
        _unloadPendingResources.pop_front();
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
    return _loadedPathes.find(path) != _loadedPathes.end()
        ||  std::find_if(
                _loadPendingResources.begin(),
                _loadPendingResources.end(),
                [path] (const ResourceDescriptor & descriptor) {
                    return path == descriptor.path;
                }
            ) != _loadPendingResources.end();
}

bool Engine::ResourceManager::isNameUsed(
    const std::string & name,
    ResourceType type
) const noexcept {
    return _resources[type].find(name) != _resources[type].end()
        ||  std::find_if(
                _loadPendingResources.begin(),
                _loadPendingResources.end(),
                [name, type] (const ResourceDescriptor & descriptor) {
                    return name == descriptor.name && descriptor.type == type;
                }
            ) != _loadPendingResources.end();
}

std::unique_ptr<Engine::Resource> Engine::ResourceManager::loadResource(
    const ResourceDescriptor & descriptor
) const noexcept {
    auto loader = _loaders[descriptor.type].find(descriptor.path.extension());

    if (loader != _loaders[descriptor.type].end()) {
        return loader->second->load(descriptor);
    } else {
        _logger->log(
            Logging::Level::Error,
            "[Resource Manager] No loader available for this type of file: {}",
            descriptor.path.string()
        );
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
    _loaders[ResourceType::MeshType]
        = std::map<std::filesystem::path, std::unique_ptr<IResourceLoader>>();
    _loaders[ResourceType::MeshType][".obj"]
        = std::make_unique<ObjMeshLoader>();

    _loaders[ResourceType::ShaderType]
        = std::map<std::filesystem::path, std::unique_ptr<IResourceLoader>>();
    _loaders[ResourceType::ShaderType][".spv"]
        = std::make_unique<SpirvShaderLoader>();

    _loaders[ResourceType::TextureType]
        = std::map<std::filesystem::path, std::unique_ptr<IResourceLoader>>();
    _loaders[ResourceType::TextureType][".png"]
        = std::make_unique<GenericTextureLoader>();
    _loaders[ResourceType::TextureType][".jpg"]
        = std::make_unique<GenericTextureLoader>();
    _loaders[ResourceType::TextureType][".jpeg"]
        = std::make_unique<GenericTextureLoader>();
    _loaders[ResourceType::TextureType][".tga"]
        = std::make_unique<GenericTextureLoader>();

    _loaders[ResourceType::TextType]
        = std::map<std::filesystem::path, std::unique_ptr<IResourceLoader>>();
    _loaders[ResourceType::TextType][".txt"]
        = std::make_unique<TextTxtLoader>();
}

void Engine::ResourceManager::initializeResourceContainers() noexcept
{
    _resources = {
        ResourceContainer(),
        ResourceContainer(),
        ResourceContainer()
    };
}
