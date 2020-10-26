#include "Engine/Resources/Loaders/Meshes/MeshObjLoader.hpp"

#include "Engine/Exceptions/ParsingException.hpp"
#include "Engine/Resources/Mesh.hpp"
#include "Engine/Resources/MeshResource.hpp"
#include "Engine/StringUtils.hpp"

#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include <iostream> // TODO remove once the logger is implemented

std::unique_ptr<Engine::Resource> Engine::MeshObjLoader::load(
    const ResourceDescriptor & descriptor
) noexcept {
    std::ifstream file(descriptor.path);

    if (!file.is_open()) {
        return nullptr;
    }
    Mesh mesh;
    std::vector<vec3<float>> vertices;
    std::vector<vec3<float>> normals;
    std::vector<vec2<float>> texCoords;
    std::size_t lineNumber = 1;
    std::string line;

    try {
        while (std::getline(file, line)) {
            trimString(line);
            auto elements = splitString(line, " ");

            if (elements.size() < 1) {
                continue;
            } else if (elements[0].size() > 0 && elements[0][0] == '#') {
                continue;
            } else if (elements[0] == "v") {
                vertices.push_back(parseVertex(elements));
            } else if (elements[0] == "vn") {
                normals.push_back(parseNormal(elements));
            } else if (elements[0] == "vt") {
                texCoords.push_back(parseUvCoordinates(elements));
            } else if (elements[0] == "f") {
                parsePolygon(elements, vertices, normals, texCoords, mesh);
            } else {
                std::cerr   << "[MeshLoader][" << descriptor.path << "] "
                            << "unsupported parameter at line " << lineNumber
                            << ": " << elements[0] << std::endl;
            }
            lineNumber++;
        }
    } catch (const std::exception & exception) {
        std::cerr   << "[MeshLoader][" << descriptor.path << "] "
                    << "Could not parse line " << lineNumber
                    << ": " << exception.what() << std::endl;
        return nullptr;
    }
    return std::make_unique<MeshResource>(
        descriptor.name,
        descriptor.path,
        std::move(mesh)
    );
}

Engine::vec3<float> Engine::MeshObjLoader::parseVertex(
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

Engine::vec3<float> Engine::MeshObjLoader::parseNormal(
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

Engine::vec2<float> Engine::MeshObjLoader::parseUvCoordinates(
    const std::vector<std::string> & elements
) {
    if (elements.size() < 3 || elements.size() > 4) {
        throw Engine::ParsingException("Invalid format for uv coordinates definition");
    }
    return {
        std::stof(elements[1]),
        std::stof(elements[2])
    };
}

void Engine::MeshObjLoader::parsePolygon(
    const std::vector<std::string> & elements,
    const std::vector<vec3<float>> & vertices,
    const std::vector<vec3<float>> & normals,
    const std::vector<vec2<float>> & texCoords,
    Mesh & mesh
) {
    if (elements.size() != 4) {
        throw Engine::ParsingException("Invalid format for polygon definition");
    }
    std::regex regex("([0-9]+)\/([0-9]+)?\/([0-9]+)?");

    for (std::size_t i = 1; i < elements.size(); ++i) {
        std::smatch match;

        if (!std::regex_match(elements[i], match, regex)) {
            throw ParsingException("Invalid format for face definition");
        }
        uint32_t vertexIndex = std::stoi(match[1]);

        mesh.vertices.emplace_back(vertices[vertexIndex - 1]);

        if (match[2].length() > 0) {
            uint32_t texIndex = std::stoi(match[2]);

            mesh.texCoordinates.emplace_back(texCoords[texIndex - 1]);
        }
        if (match[3].length() > 0) {
            uint32_t normalIndex = std::stoi(match[3]);

            mesh.normals.emplace_back(normals[normalIndex - 1]);
        }
        mesh.indices.push_back(mesh.vertices.size() - 1);
    }
}
