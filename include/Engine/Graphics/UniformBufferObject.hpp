#ifndef ENGINE_GRAPHICS_UNIFORM_BUFFER_OBJECT_HPP_
#define ENGINE_GRAPHICS_UNIFORM_BUFFER_OBJECT_HPP_

#include "Engine/Maths/matrix4.hpp"

namespace Engine {

struct UniformBufferObject {
    Math::Matrix4 model;
    Math::Matrix4 view;
    Math::Matrix4 proj;
};

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_UNIFORM_BUFFER_OBJECT_HPP_ */
