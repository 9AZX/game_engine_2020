#ifndef ENGINE_RESOURCE_MESH_RESOURCE_HPP_
#define ENGINE_RESSOURC_MESH_RESOURCE_HPP_

#include "Engine/Resource/Mesh.hpp"
#include "Engine/Resource/Resource.hpp"

namespace Engine {

class MeshResource: public Resource {
    public:
        MeshResource(
            const std::string & name,
            const std::filesystem::path & path,
            const Mesh & mesh
        );
        MeshResource(
            const std::string & name,
            const std::filesystem::path & path,
            Mesh && mesh
        );

        ResourceType getType() const noexcept override;
        const Mesh & getMesh() const noexcept;

    private:
        Mesh _mesh;

}; /* class MeshResource */

} /* namespace Engine */

#endif /* ENGINE_RESOURCE_MESH_RESOURCE_HPP_ */
