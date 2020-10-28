#include "Engine/Resources/MeshResource.hpp"

Engine::MeshResource::MeshResource(
    const std::string & name,
    const std::filesystem::path & path
):
    Resource(name, path)
{
}

Engine::MeshResource::MeshResource(const MeshResource & mesh):
    Resource(mesh.getName(), mesh.getPath()),
    _vertices(mesh._vertices),
    _normals(mesh._normals),
    _textureCoordinates(mesh._textureCoordinates),
    _indices(mesh._indices)
{
}

Engine::MeshResource::MeshResource(MeshResource && mesh):
    Resource(mesh.getName(), mesh.getPath()),
    _vertices(std::move(mesh._vertices)),
    _normals(std::move(mesh._normals)),
    _textureCoordinates(std::move(mesh._textureCoordinates)),
    _indices(std::move(mesh._indices))
{
}

Engine::MeshResource & Engine::MeshResource::operator = (
    const MeshResource & other
) noexcept {
    if (&other == this) {
        return *this;
    }
    _vertices = other._vertices;
    _normals = other._normals;
    _textureCoordinates = other._textureCoordinates;
    _indices = other._indices;
    return *this;
}

Engine::MeshResource & Engine::MeshResource::operator = (
    MeshResource && other
) noexcept {
    if (&other == this) {
        return *this;
    }
    _vertices = std::move(other._vertices);
    _normals = std::move(other._normals);
    _textureCoordinates = std::move(other._textureCoordinates);
    _indices = std::move(other._indices);
    return *this;
}

Engine::ResourceType Engine::MeshResource::getType() const noexcept
{
    return ResourceType::MeshType;
}

const std::vector<Engine::vec3f> & Engine::MeshResource::getVertices() const noexcept
{
    return _vertices;
}

const std::vector<Engine::vec3f> & Engine::MeshResource::getNormals() const noexcept
{
    return _normals;
}

const std::vector<Engine::vec2f> & Engine::MeshResource::getTextureCoordinates() const noexcept
{
    return _textureCoordinates;
}

const std::vector<std::uint32_t> & Engine::MeshResource::getIndices() const noexcept
{
    return _indices;
}

std::vector<Engine::vec3f> & Engine::MeshResource::getVertices() noexcept
{
    return _vertices;
}

std::vector<Engine::vec3f> & Engine::MeshResource::getNormals() noexcept
{
    return _normals;
}

std::vector<Engine::vec2f> & Engine::MeshResource::getTextureCoordinates() noexcept
{
    return _textureCoordinates;
}

std::vector<std::uint32_t> & Engine::MeshResource::getIndices() noexcept
{
    return _indices;
}
