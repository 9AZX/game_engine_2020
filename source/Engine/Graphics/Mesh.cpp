#include "Engine/Graphics/Mesh.hpp"

Engine::Mesh::Mesh(
    const std::string & name,
    const std::filesystem::path & path
):
    Resource(name, path)
{
}

Engine::Mesh::Mesh(const Mesh & mesh):
    Resource(mesh.getName(), mesh.getPath()),
    vertices(mesh.vertices),
    indices(mesh.indices)
{
}

Engine::Mesh::Mesh(Mesh && mesh):
    Resource(mesh.getName(), mesh.getPath()),
    vertices(std::move(mesh.vertices)),
    indices(std::move(mesh.indices))
{
}

Engine::Mesh & Engine::Mesh::operator = (const Mesh & mesh) noexcept
{
    if (&mesh == this) {
        return *this;
    }
    vertices = mesh.vertices;
    indices = mesh.indices;
    return *this;
}

Engine::Mesh & Engine::Mesh::operator = (Mesh && mesh) noexcept
{
    if (&mesh == this) {
        return *this;
    }
    vertices = std::move(mesh.vertices);
    indices = std::move(mesh.indices);
    return *this;
}

Engine::ResourceType Engine::Mesh::getType() const noexcept
{
    return ResourceType::MeshType;
}
