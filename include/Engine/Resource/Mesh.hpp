#ifndef ENGINE_RESOURCE_MESH_HPP_
#define ENGINE_RESOURCE_MESH_HPP_

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

struct Mesh {
    std::vector<vec2<float>> _uv;
    std::vector<vec3<float>> _normals;
    std::vector<vec3<float>> _vertices;
}; /* class Mesh */

} /* namespace Engine */

#endif /* ENGINE_RESOURCE_MESH_HPP_ */
