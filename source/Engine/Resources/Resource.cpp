#include "Engine/Resources/Resource.hpp"

Engine::Resource::Resource() {}

Engine::Resource::Resource(
    const std::string & name,
    const std::filesystem::path & path
):
    _name(name),
    _path(path)
{

}

const std::string & Engine::Resource::getName() const noexcept
{
    return _name;
}

const std::filesystem::path & Engine::Resource::getPath() const noexcept
{
    return _path;
}
