#include "Engine/Resources/Loaders/Textures/TextureGenericLoader.hpp"

#include <Engine/Resources/TextureResource.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::unique_ptr<Engine::Resource> Engine::TextureGenericLoader::load(
    const ResourceDescriptor & descriptor
) noexcept {
    int width;
    int height;
    int comp;
    unsigned char * image = stbi_load(
        static_cast<const char *>(descriptor.path.u8string().c_str()),
        &width,
        &height,
        &comp,
        STBI_rgb_alpha
    );

    std::unique_ptr<TextureResource> texture = std::make_unique<TextureResource>(
        descriptor.name,
        descriptor.path,
        static_cast<std::uint32_t>(width),
        static_cast<std::uint32_t>(height),
        std::vector<std::uint8_t>(image, image + (width * height * 4))
    );
    stbi_image_free(image);
    return std::move(texture);
}
