#include "Engine/Resources/ShaderResource.hpp"

Engine::ShaderResource::ShaderResource(
    const std::string & name,
    const std::filesystem::path & path,
    const std::vector<char> & shader
):
    Resource(name, path),
    _shader(shader)
{
}

Engine::ShaderResource::ShaderResource(
    const std::string & name,
    const std::filesystem::path & path,
    std::vector<char> && shader
):
    Resource(name, path),
    _shader(std::move(shader))
{
}

Engine::ShaderResource::ShaderResource(
    const ShaderResource & shader
):
    _shader(shader._shader)
{
}

Engine::ShaderResource::ShaderResource(
    ShaderResource && shader
):
    _shader(std::move(shader._shader))
{
}

Engine::ShaderResource & Engine::ShaderResource::operator = (
    const ShaderResource & shader
) noexcept {
    if (&shader == this) {
        return *this;
    }
    _shader = shader._shader;
    return *this;
}

Engine::ShaderResource & Engine::ShaderResource::operator = (
    ShaderResource && shader
) noexcept {
    if (&shader == this) {
        return *this;
    }
    _shader = std::move(shader._shader);
    return *this;
}

Engine::ResourceType Engine::ShaderResource::getType() const noexcept
{
    return Engine::ResourceType::ShaderType;
}

const std::vector<char> & Engine::ShaderResource::getShader() const noexcept
{
    return _shader;
}

std::vector<char> & Engine::ShaderResource::getShader() noexcept
{
    return _shader;
}
