#ifndef ENGINE_MATHS_VECTOR2_HPP_
#define ENGINE_MATHS_VECTOR2_HPP_

namespace Engine {

namespace Math {

struct vec2f {
    float x;
    float y;

    bool operator == (const vec2f & other) const noexcept;
}; /* struct vec2f */

} /* namespace Math */

} /* namespace Engine */

#endif /* ENGINE_MATHS_VECTOR2_HPP_ */
