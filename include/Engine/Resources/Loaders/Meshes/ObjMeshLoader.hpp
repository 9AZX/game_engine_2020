#ifndef ENGINE_RESOURCES_LOADERS_MESHES_OBJ_MESH_LOADER_HPP_
#define ENGINE_RESOURCES_LOADERS_MESHES_OBJ_MESH_LOADER_HPP_

#include "Engine/Graphics/Mesh.hpp"
#include "Engine/Logging/Logger.hpp"
#include "Engine/Maths/Vector2.hpp"
#include "Engine/Maths/Vector3.hpp"
#include "Engine/Resources/IResourceLoader.hpp"

#include <functional>
#include <memory>
#include <regex>
#include <unordered_map>

namespace Engine {

class ObjMeshLoader: public IResourceLoader {
    public:
        ObjMeshLoader(std::shared_ptr<Logging::Logger> logger);

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
            std::vector<Math::Vector3> vertices;
            std::vector<Math::Vector3> normals;
            std::vector<Math::Vector2> texCoords;
            std::unordered_map<VertexIndex, std::size_t, VertexIndexHash> vertexMap;
            bool hasNormals = false;
            bool hasTexCoordinates = false;
            Mesh mesh;
        };

        static Math::Vector3 parseVertex(
            const std::vector<std::string> & elements
        );
        static Math::Vector3 parseNormal(
            const std::vector<std::string> & elements
        );
        static Math::Vector2 parseUvCoordinates(
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

        std::shared_ptr<Logging::Logger> _logger;
}; /* class ObjMeshLoader */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_LOADERS_MESHES_OBJ_MESH_LOADER_HPP_ */
