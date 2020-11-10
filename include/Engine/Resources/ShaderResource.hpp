#ifndef ENGINE_RESOURCES_SHADER_RESOURCE_HPP_
#define ENGINE_RESOURCES_SHADER_RESOURCE_HPP_

#include "Engine/Resources/Resource.hpp"

#include <vector>

namespace Engine {

class ShaderResource: public Resource {
    public:
        ShaderResource(
            const std::string & name,
            const std::filesystem::path & path,
            const std::vector<char> & shader
        );
        ShaderResource(
            const std::string & name,
            const std::filesystem::path & path,
            std::vector<char> && shader
        );
        ShaderResource(const ShaderResource & shader);
        ShaderResource(ShaderResource && shader);

        ShaderResource & operator = (const ShaderResource & resource) noexcept;
        ShaderResource & operator = (ShaderResource && resource) noexcept;

        ResourceType getType() const noexcept override;
        const std::vector<char> & getShader() const noexcept;
        std::vector<char> & getShader() noexcept;

    private:
        std::vector<char> _shader;
}; /* class ShaderResource */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_SHADER_RESOURCE_HPP_ */
