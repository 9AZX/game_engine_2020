#ifndef ENGINE_GRAPHICS_MESH_HPP_
#define ENGINE_GRAPHICS_MESH_HPP_

#include "Engine/Graphics/Vertex.hpp"
#include "Engine/Resources/Resource.hpp"

#include <cstdint>
#include <vector>

namespace Engine {

class Mesh: public Resource {
    public:
        Mesh(
            const std::string & name = "",
            const std::filesystem::path & path = ""
        );
        Mesh(const Mesh & mesh);
        Mesh(Mesh && mesh);
        ~Mesh() = default;

        Mesh & operator = (const Mesh & mesh) noexcept;
        Mesh & operator = (Mesh && mesh) noexcept;

        ResourceType getType() const noexcept override;

        std::vector<Vertex> vertices;
        std::vector<std::uint32_t> indices;
}; /* class Mesh */

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_MESH_HPP_ */
