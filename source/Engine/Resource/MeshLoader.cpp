#include "Engine/Resource/MeshLoader.hpp"

#include "Engine/Exception/ParsingException.hpp"
#include "Engine/Resource/Mesh.hpp"
#include "Engine/Resource/MeshResource.hpp"
#include "Engine/StringUtils.hpp"

#include <fstream>
#include <string>
#include <vector>

#include <iostream>

Engine::vec3<float> parseVertex(
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

Engine::vec3<float> parseNormal(
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

Engine::vec2<float> parseUvCoordinates(
    const std::vector<std::string> & elements
) {
    if (elements.size() < 3 || elements.size() > 4) {
        throw Engine::ParsingException("Invallid format for uv coordinates definition");
    }
    return {
        std::stof(elements[1]),
        std::stof(elements[2])
    };
}

void parsePolygon(
    const std::vector<std::string> & elements
) {
    if (elements.size() != 4) {
        throw Engine::ParsingException("Invalid format for polygon definition");
    }
}

std::unique_ptr<Engine::Resource> Engine::loadMesh(const ResourceDescriptor & descriptor) noexcept
{
    std::ifstream file(descriptor.path);

    if (!file.is_open()) {
        return nullptr;
    }
    Mesh mesh;
    std::vector<vec3<float>> vertices;
    std::vector<vec3<float>> normals;
    std::vector<vec2<float>> uvCoords;
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
                uvCoords.push_back(parseUvCoordinates(elements));
            } else if (elements[0] == "f") {
                
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
