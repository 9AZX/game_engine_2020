#ifndef ENGINE_RESOURCES_SHADER_RESOURCE_HPP_
#define ENGINE_RESOURCES_SHADER_RESOURCE_HPP_

#include "Engine/Resources/Resource.hpp"

#include <vector>

namespace Engine
{

    class ShaderResource : public Resource
    {
    public:
        ShaderResource(
            const std::string &name,
            const std::filesystem::path &path,
            const std::vector<unsigned int> &shader);
        ShaderResource(
            const std::string &name,
            const std::filesystem::path &path,
            std::vector<unsigned int> &&shader);
        ShaderResource(const ShaderResource &shader);
        ShaderResource(ShaderResource &&shader);

        ShaderResource &operator=(const ShaderResource &resource) noexcept;
        ShaderResource &operator=(ShaderResource &&resource) noexcept;

        ResourceType getType() const noexcept override;
        const std::vector<unsigned int> &getShader() const noexcept;
        std::vector<unsigned int> &getShader() noexcept;

    private:
        std::vector<unsigned int> _shader;
    }; /* class ShaderResource */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_SHADER_RESOURCE_HPP_ */
