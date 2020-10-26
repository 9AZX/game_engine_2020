#ifndef ENGINE_RESOURCES_LOADERS_MESHES_MESH_OBJ_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_MESHES_MESH_OBJ_LOADER_HPP_

#include "Engine/Resources/IResourceLoader.hpp"
#include "Engine/Resources/Mesh.hpp"

namespace Engine {

class MeshObjLoader: public IResourceLoader {
    public:
        std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept override;

    private:
        static Engine::vec3<float> parseVertex(
            const std::vector<std::string> & elements
        );
        static Engine::vec3<float> parseNormal(
            const std::vector<std::string> & elements
        );
        static Engine::vec2<float> parseUvCoordinates(
            const std::vector<std::string> & elements
        );
        static void parsePolygon(
            const std::vector<std::string> & elements,
            const std::vector<vec3<float>> & vertices,
            const std::vector<vec3<float>> & normals,
            const std::vector<vec2<float>> & texCoords,
            Mesh & mesh
        );
}; /* class ObjLoader */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_LOADERS_MESHES_MESH_OBJ_LOADER_HPP_ */
