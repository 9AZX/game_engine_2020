#ifndef ENGINE_RESOURCES_MESH_HPP_
#define ENGINE_RESOURCES_MESH_HPP_

#include <cstdint>
#include <functional>
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

struct Mesh
{
    std::vector<vec3f> vertices;
    std::vector<vec3f> normals;
    std::vector<vec2f> texCoordinates;
    std::vector<std::uint32_t> indices;
}; /* class Mesh */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_MESH_HPP_ */
