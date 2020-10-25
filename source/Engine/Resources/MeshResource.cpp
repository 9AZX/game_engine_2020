#include "Engine/Resources/MeshResource.hpp"

Engine::MeshResource::MeshResource(
    const std::string & name,
    const std::filesystem::path & path,
    const Mesh & mesh
):
    Resource(name, path),
    _mesh(mesh)
{
}

Engine::MeshResource::MeshResource(
    const std::string & name,
    const std::filesystem::path & path,
    Mesh && mesh
):
    Resource(name, path),
    _mesh(std::move(mesh))
{
}

Engine::ResourceType Engine::MeshResource::getType() const noexcept
{
    return ResourceType::MeshType;
}

const Engine::Mesh & Engine::MeshResource::getMesh() const noexcept
{
    return _mesh;
}
