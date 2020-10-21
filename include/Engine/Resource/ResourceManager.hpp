#ifndef ENGINE_RESOURCE_RESOURCE_MANAGER_HPP_
#define ENGINE_RESOURCE_RESOURCE_MANAGER_HPP_

#include "Resource.hpp"
#include "ResourceDescriptor.hpp"
#include "ResourceType.hpp"

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
    using ResourceLoader = std::unique_ptr<Resource> (*)(const ResourceDescriptor & descriptor);

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

        std::array<std::map<std::filesystem::path, ResourceLoader>, ResourceType::MAX_VALUE> _loaders;
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

#endif /* ENGINE_RESOURCE_RESOURCE_MANAGER_HPP_ */
