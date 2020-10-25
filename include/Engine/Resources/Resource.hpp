#ifndef ENGINE_RESOURCES_RESOURCE_HPP_
#define ENGINE_RESOURCES_RESOURCE_HPP_

#include "Engine/Resources/ResourceType.hpp"

#include <filesystem>
#include <string>

namespace Engine {

class Resource {
    public:
        Resource();
        virtual ~Resource() = default;

        virtual ResourceType getType() const noexcept = 0;
        const std::string & getName() const noexcept;
        const std::filesystem::path & getPath() const noexcept;

    protected:
        Resource(const std::string & name, const std::filesystem::path & path);

    private:
        std::string _name;
        std::filesystem::path _path;

}; /* class Resource */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_RESOURCE_HPP_ */
