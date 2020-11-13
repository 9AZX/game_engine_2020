#ifndef ENGINE_MATHS_VECTOR3_HPP_
#define ENGINE_MATHS_VECTOR3_HPP_

namespace Engine {

namespace Math {

struct vec3f {
    float x;
    float y;
    float z;

    bool operator == (const vec3f & other) const noexcept;
}; /* struct vec3f */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_VECTOR3_HPP_ */
