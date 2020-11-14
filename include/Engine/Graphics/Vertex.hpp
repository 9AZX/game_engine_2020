#ifndef ENGINE_GRAPHICS_VERTEX_HPP_
#define ENGINE_GRAPHICS_VERTEX_HPP_

#include "Engine/Maths/Vector2.hpp"
#include "Engine/Maths/Vector3.hpp"

#include <array>
#include <vulkan/vulkan.hpp>

namespace Engine {

class Vertex {
    public:
        Math::Vector3 position;
        Math::Vector3 normal;
        Math::Vector3 color;
        Math::Vector2 textureCoordinates;

        bool operator == (const Vertex & other) const noexcept;

        static vk::VertexInputBindingDescription getBindingDescription() noexcept;
        static std::array<vk::VertexInputAttributeDescription, 4> getAttributeDescriptions() noexcept;
}; /* class Vertex */

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_VERTEX_HPP_ */
