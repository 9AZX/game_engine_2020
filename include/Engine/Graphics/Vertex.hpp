#ifndef ENGINE_GRAPHICS_VERTEX_HPP_
#define ENGINE_GRAPHICS_VERTEX_HPP_

#include "Engine/Maths/Vector2.hpp"
#include "Engine/Maths/Vector3.hpp"

#include <array>
#include <vulkan/vulkan.hpp>

namespace Engine {

class Vertex {
    public:
        Math::vec3f position;
        Math::vec3f normal;
        Math::vec3f color;
        Math::vec2f textureCoordinates;

        bool operator == (const Vertex & other) const noexcept;

        static vk::VertexInputBindingDescription getBindingDescription() noexcept;
        static std::array<vk::VertexInputAttributeDescription, 4> getAttributeDescriptions() noexcept;
}; /* class Vertex */

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_VERTEX_HPP_ */
