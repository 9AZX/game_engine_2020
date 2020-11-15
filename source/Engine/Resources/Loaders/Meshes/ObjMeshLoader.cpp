#include "Engine/Resources/Loaders/Meshes/ObjMeshLoader.hpp"

#include "Engine/Exceptions/ParsingException.hpp"
#include "Engine/StringUtils.hpp"

#include <fstream>
#include <regex>
#include <string>
#include <vector>

Engine::ObjMeshLoader::ObjMeshLoader(std::shared_ptr<Logging::Logger> logger):
    _logger(logger)
{
}

std::unique_ptr<Engine::Resource> Engine::ObjMeshLoader::load(
    const ResourceDescriptor & descriptor
) noexcept {
    std::ifstream file(descriptor.path);

    if (!file.is_open()) {
        return nullptr;
    }
    ParsingContext context;
    std::size_t lineNumber = 0;
    std::string line;

    try {
        while (std::getline(file, line)) {
            trimString(line);
            auto elements = splitString(line, " ");

            lineNumber++;
            if (elements.size() < 1) {
                continue;
            } else if (elements[0].size() > 0 && elements[0][0] == '#') {
                continue;
            } else if (elements[0] == "v") {
                context.vertices.push_back(parseVertex(elements));
            } else if (elements[0] == "vn") {
                context.normals.push_back(parseNormal(elements));
            } else if (elements[0] == "vt") {
                context.texCoords.push_back(parseUvCoordinates(elements));
            } else if (elements[0] == "f") {
                parsePolygon(elements, context);
            } else {
                _logger->log(
                    Logging::Level::Debug,
                    "[Mesh Loader] {}: unsupported parameter at line {}: {}",
                    descriptor.path.string(),
                    lineNumber,
                    elements[0]
                );
            }
        }
    } catch (const std::exception & exception) {
        _logger->log(
            Logging::Level::Error,
            "[Mesh Loader] {}: could not parse line {}: {}",
            descriptor.path.string(),
            lineNumber,
            exception.what()
        );
        return nullptr;
    }
    std::unique_ptr<Mesh> resource = std::make_unique<Mesh>(
        descriptor.name,
        descriptor.path
    );
    *resource = std::move(context.mesh);
    return std::move(resource);
}

Engine::Math::Vector3 Engine::ObjMeshLoader::parseVertex(
    const std::vector<std::string> & elements
) {
    if (elements.size() < 4 || elements.size() > 5) {
        throw Engine::ParsingException("Invalid format for vertex definition");
    }
    return {
        std::stof(elements[1]),
        std::stof(elements[2]),
        std::stof(elements[3])
    };
}

Engine::Math::Vector3 Engine::ObjMeshLoader::parseNormal(
    const std::vector<std::string> & elements
) {
    if (elements.size() != 4) {
        throw Engine::ParsingException("Invalid format for normal definition");
    }
    return {
        std::stof(elements[1]),
        std::stof(elements[2]),
        std::stof(elements[3])
    };
}

Engine::Math::Vector2 Engine::ObjMeshLoader::parseUvCoordinates(
    const std::vector<std::string> & elements
) {
    if (elements.size() < 3 || elements.size() > 4) {
        throw Engine::ParsingException("Invalid format for uv coordinates definition");
    }
    return {
        std::stof(elements[1]),
        1.0f - std::stof(elements[2])
    };
}

void Engine::ObjMeshLoader::parsePolygon(
    const std::vector<std::string> & elements,
    ParsingContext & context
) {
    if (elements.size() != 4) {
        throw Engine::ParsingException("Invalid format for polygon definition");
    }
    std::regex regex("^(\\d+)\/?(\\d*)\/?(\\d*)$");

    for (std::size_t i = 1; i < elements.size(); ++i) {
        std::smatch match;

        if (!std::regex_match(elements[i], match, regex)) {
            throw ParsingException("Invalid polygon definition");
        }
        if (context.mesh.indices.size() == 0) {
            detectPolygonMode(context, match);
        }
        VertexIndex index = parseIndices(context, match);
        validateIndices(context, index);

        auto pair = context.vertexMap.find(index);

        if (pair == context.vertexMap.end()) {
            std::size_t meshIndex = context.mesh.vertices.size();
            Vertex vertex {};

            vertex.position = context.vertices[index.vertexIndex];
            vertex.color = { 0.0f, 0.0f, 0.0f };
            if (context.hasTexCoordinates) {
                vertex.textureCoordinates = context.texCoords[index.texIndex];
            }
            if (context.hasNormals) {
                vertex.normal = context.normals[index.normalIndex];
            }
            context.mesh.vertices.emplace_back(vertex);
            context.mesh.indices.emplace_back(
                static_cast<std::uint32_t>(meshIndex)
            );
            context.vertexMap[index] = meshIndex;
        } else {
            context.mesh.indices.emplace_back(
                static_cast<std::uint32_t>(pair->second)
            );
        }
    }
}

void Engine::ObjMeshLoader::detectPolygonMode(
    ParsingContext & context,
    const std::smatch & match
) {
    if (match.size() == 3) {
        if (match[2].length() > 0) {
            context.hasTexCoordinates = true;
        }
    } else if (match.size() == 4) {
        if (match[2].length() > 0) {
            context.hasTexCoordinates = true;
        }
        if (match[3].length() > 0) {
            context.hasNormals = true;
        }
    }
}

Engine::ObjMeshLoader::VertexIndex Engine::ObjMeshLoader::parseIndices(
    const ParsingContext & context,
    const std::smatch & match
) {
    if (match.size() == 2) {
        if (context.hasNormals || context.hasTexCoordinates) {
            throw ParsingException("Lines defining polygons don't share the same syntax");
        }
    } else if (match.size() == 3) {
        if (context.hasNormals || !context.hasTexCoordinates) {
            throw ParsingException("Lines defining polygons don't share the same syntax");
        }
    } else if (match.size() == 4) {
        if ((!context.hasNormals && match[3].length() > 0)
            || (!context.hasTexCoordinates && match[2].length() > 0)
        ) {
            throw ParsingException("Lines defining polygons don't share the same syntax");
        }
    }
    VertexIndex index;

    index.vertexIndex = std::stoi(match[1]) - 1;
    index.texIndex = (context.hasTexCoordinates) ? std::stoi(match[2]) - 1 : 0;
    index.normalIndex = (context.hasNormals) ? std::stoi(match[3]) - 1 : 0;
    return index;
}

void Engine::ObjMeshLoader::validateIndices(
    const ParsingContext & context,
    const VertexIndex & index
) {
    if (index.vertexIndex >= context.vertices.size()) {
        throw ParsingException(
            "Vertex index is greater than the vertex array size"
        );
    }
    if (context.hasTexCoordinates
        && index.texIndex >= context.texCoords.size())
    {
        throw ParsingException(
            "Texture coordinates index is greater than the texture "
            "coordinates array size"
        );
    }
    if (context.hasNormals && index.normalIndex >= context.normals.size()) {
        throw ParsingException(
            "Texture coordinates index is greater than the texture "
            "coordinates array size"
        );
    }
}
