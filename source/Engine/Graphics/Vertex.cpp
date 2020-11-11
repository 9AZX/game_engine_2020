#include "Engine/Graphics/Mesh.hpp"

bool Engine::Vertex::operator == (const Vertex & other) const noexcept
{
    return position == other.position
        && normal == other.normal
        && color == other.color
        && textureCoordinates == other.textureCoordinates;
}

vk::VertexInputBindingDescription Engine::Vertex::getBindingDescription() noexcept
{
    vk::VertexInputBindingDescription bindingDescription {};

    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = vk::VertexInputRate::eVertex;
    return bindingDescription;
}

std::array<vk::VertexInputAttributeDescription, 4> Engine::Vertex::getAttributeDescriptions() noexcept
{
    std::array<vk::VertexInputAttributeDescription, 4> attributeDescriptions {};

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = vk::Format::eR32G32B32Sfloat;
    attributeDescriptions[0].offset = offsetof(Vertex, position);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = vk::Format::eR32G32B32Sfloat;
    attributeDescriptions[1].offset = offsetof(Vertex, normal);

    attributeDescriptions[2].binding = 0;
    attributeDescriptions[2].location = 2;
    attributeDescriptions[2].format = vk::Format::eR32G32B32Sfloat;
    attributeDescriptions[2].offset = offsetof(Vertex, color);

    attributeDescriptions[3].binding = 0;
    attributeDescriptions[3].location = 3;
    attributeDescriptions[3].format = vk::Format::eR32G32Sfloat;
    attributeDescriptions[3].offset = offsetof(Vertex, textureCoordinates);
    return attributeDescriptions;
}
