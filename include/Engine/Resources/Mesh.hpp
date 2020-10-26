#ifndef ENGINE_RESOURCES_MESH_HPP_
#define ENGINE_RESOURCES_MESH_HPP_

#include <cstdint>
#include <vector>

namespace Engine {

template <typename T>
struct vec3
{
    T x;
    T y;
    T z;
};

template <typename T>
struct vec2
{
    T x;
    T y;
};

struct Mesh
{
    std::vector<vec3<float>> vertices;
    std::vector<vec3<float>> normals;
    std::vector<vec2<float>> texCoordinates;
    std::vector<std::uint32_t> indices;
}; /* class Mesh */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_MESH_HPP_ */
