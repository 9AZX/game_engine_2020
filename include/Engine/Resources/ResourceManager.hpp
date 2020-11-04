#ifndef ENGINE_RESOURCES_RESOURCE_MANAGER_HPP_
#define ENGINE_RESOURCES_RESOURCE_MANAGER_HPP_

#include "Engine/Resources/IResourceLoader.hpp"
#include "Engine/Resources/Resource.hpp"
#include "Engine/Resources/ResourceDescriptor.hpp"
#include "Engine/Resources/ResourceType.hpp"

#include <array>
#include <filesystem>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>

namespace Engine {

class ResourceManager {

    using ResourceContainer = std::map<std::string, std::unique_ptr<Resource>>;

    public:
        ResourceManager();
        ResourceManager(bool allowDuplicates);
        ~ResourceManager() = default;

        void init() noexcept;

        bool registerResource(
            const std::string & name,
            ResourceType type,
            const std::filesystem::path & path
        ) noexcept;
        bool registerResource(const ResourceDescriptor & descriptor) noexcept;
        void unregisterResource(const std::string & name, ResourceType type) noexcept;

        bool loadResources() noexcept;
        void unloadResources() noexcept;

        Resource * getResource(const std::string & name, ResourceType type) noexcept;

    private:
        bool isResourceLoaded(const std::filesystem::path & path) const noexcept;
        bool isNameUsed(const std::string & name, ResourceType type) const noexcept;
        std::unique_ptr<Resource> loadResource(const ResourceDescriptor & descriptor) const noexcept;

        void defaultInitialize() noexcept;
        void initializeLoaders() noexcept;
        void initializeResourceContainers() noexcept;

        std::array<std::map<std::filesystem::path, std::unique_ptr<IResourceLoader>>, ResourceType::MAX_VALUE> _loaders;
        std::array<ResourceContainer, ResourceType::MAX_VALUE> _resources;

        std::queue<ResourceDescriptor> _loadPendingResources;
        std::queue<ResourceDescriptor> _unloadPendingResources;
        std::set<std::filesystem::path> _loadedPathes;

        #ifdef NDEBUG
        bool _allowDuplicates = false;
        #else
        bool _allowDuplicates = true;
        #endif

}; /* class ResourceManager */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_RESOURCE_MANAGER_HPP_ */
