#ifndef ENGINE_RESOURCES_TEXTURE_RESOURCE_HPP_
#define ENGINE_RESOURCES_TEXTURE_RESOURCE_HPP_

#include "Engine/Resources/Resource.hpp"

#include <cstdint>

namespace Engine {

class TextureResource: public Resource {
    public:
        TextureResource() = default;
        TextureResource(
            const std::string & name,
            const std::filesystem::path & path,
            std::uint32_t width,
            std::uint32_t height,
            const std::vector<std::uint8_t> & data
        );
        TextureResource(
            const std::string & name,
            const std::filesystem::path & path,
            std::uint32_t width,
            std::uint32_t height,
            std::vector<std::uint8_t> && data
        );
        TextureResource(const TextureResource & texture);
        TextureResource(TextureResource && texture);
        ~TextureResource() = default;

        TextureResource & operator = (const TextureResource & other) noexcept;
        TextureResource & operator = (TextureResource && other) noexcept;

        ResourceType getType() const noexcept override;
        std::uint32_t getWidth() const noexcept;
        std::uint32_t getHeight() const noexcept;
        const std::vector<std::uint8_t> & getPixelArray() const noexcept;

    private:
        std::uint32_t _width = 0;
        std::uint32_t _height = 0;
        std::vector<std::uint8_t> _data;
}; /* class TextureResource */

} /* namespace Engine */

#endif /* ENGINE_RESOURCES_TEXTURE_RESOURCE_HPP_ */
