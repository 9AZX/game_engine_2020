#ifndef ENGINE_RESOURCES_LOADERS_MESHES_MESH_OBJ_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_MESHES_MESH_OBJ_LOADER_HPP_

#include "Engine/Resources/IResourceLoader.hpp"
#include "Engine/Resources/Mesh.hpp"

#include <functional>
#include <regex>
#include <unordered_map>

namespace Engine {

class MeshObjLoader: public IResourceLoader {
    public:
        std::unique_ptr<Resource> load(
            const ResourceDescriptor & descriptor
        ) noexcept override;

    private:
        struct VertexIndex {
            std::uint32_t vertexIndex;
            std::uint32_t normalIndex;
            std::uint32_t texIndex;

            bool operator == (const VertexIndex & other) const noexcept
            {
                return vertexIndex == other.vertexIndex
                    && normalIndex == other.normalIndex
                    && texIndex == other.texIndex;
            }
        };

        struct VertexIndexHash {
            std::size_t operator()(const VertexIndex & vertex) const noexcept
            {
                return ((std::hash<std::uint32_t>()(vertex.vertexIndex) ^
                   (std::hash<std::uint32_t>()(vertex.normalIndex) << 1)) >> 1) ^
                   (std::hash<std::uint32_t>()(vertex.texIndex) << 1);
            }
        };

        struct ParsingContext {
            std::vector<vec3f> vertices;
            std::vector<vec3f> normals;
            std::vector<vec2f> texCoords;
            std::unordered_map<VertexIndex, std::size_t, VertexIndexHash> vertexMap;
            bool hasNormals = false;
            bool hasTexCoordinates = false;
            Mesh mesh;
        };

        static vec3f parseVertex(
            const std::vector<std::string> & elements
        );
        static vec3f parseNormal(
            const std::vector<std::string> & elements
        );
        static vec2f parseUvCoordinates(
            const std::vector<std::string> & elements
        );

        static void parsePolygon(
            const std::vector<std::string> & elements,
            ParsingContext & context
        );

        static void detectPolygonMode(
            ParsingContext & context,
            const std::smatch & match
        );

        static VertexIndex parseIndices(
            const ParsingContext & context,
            const std::smatch & match
        );

        static void validateIndices(
            const ParsingContext & context,
            const VertexIndex & index
        );
}; /* class ObjLoader */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_LOADERS_MESHES_MESH_OBJ_LOADER_HPP_ */
