#ifndef ENGINE_RESOURCES_MESH_RESOURCE_HPP_
#define ENGINE_RESOURCES_MESH_RESOURCE_HPP_

#include "Engine/Resources/Resource.hpp"

#include <cstdint>
#include <vector>

namespace Engine {

struct vec3f
{
    float x;
    float y;
    float z;

    bool operator == (const vec3f & other) const noexcept
    {
        return x == other.x
            && y == other.y
            && z == other.z;
    }
};

struct vec2f
{
    float x;
    float y;

    bool operator == (const vec2f & other) const noexcept
    {
        return x == other.x && y == other.y;
    }
};

class MeshResource: public Resource {
    public:
        MeshResource() = default;
        MeshResource(
            const std::string & name,
            const std::filesystem::path & path
        );
        MeshResource(const MeshResource & mesh);
        MeshResource(MeshResource && mesh);
        ~MeshResource() = default;

        MeshResource & operator = (const MeshResource & other) noexcept;
        MeshResource & operator = (MeshResource && other) noexcept;

        ResourceType getType() const noexcept override;
        const std::vector<vec3f> & getVertices() const noexcept;
        const std::vector<vec3f> & getNormals() const noexcept;
        const std::vector<vec2f> & getTextureCoordinates() const noexcept;
        const std::vector<std::uint32_t> & getIndices() const noexcept;

        std::vector<vec3f> & getVertices() noexcept;
        std::vector<vec3f> & getNormals() noexcept;
        std::vector<vec2f> & getTextureCoordinates() noexcept;
        std::vector<std::uint32_t> & getIndices() noexcept;

    private:
        std::vector<vec3f> _vertices;
        std::vector<vec3f> _normals;
        std::vector<vec2f> _textureCoordinates;
        std::vector<std::uint32_t> _indices;

}; /* class MeshResource */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_MESH_RESOURCE_HPP_ */
