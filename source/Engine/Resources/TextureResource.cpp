#include "Engine/Resources/TextureResource.hpp"

Engine::TextureResource::TextureResource(
    const std::string & name,
    const std::filesystem::path & path,
    std::uint32_t width,
    std::uint32_t height,
    const std::vector<std::uint8_t> & data
):
    Resource(name, path),
    _width(width),
    _height(height),
    _data(data)
{
}

Engine::TextureResource::TextureResource(
    const std::string & name,
    const std::filesystem::path & path,
    std::uint32_t width,
    std::uint32_t height,
    std::vector<std::uint8_t> && data
):
    Resource(name, path),
    _width(width),
    _height(height),
    _data(std::move(data))
{
}

Engine::TextureResource::TextureResource(
    const TextureResource & resource
):
    Resource(resource.getName(), resource.getPath()),
    _width(resource._width),
    _height(resource._height),
    _data(resource._data)
{
}

Engine::TextureResource::TextureResource(
    TextureResource && resource
):
    Resource(resource.getName(), resource.getPath()),
    _width(resource._width),
    _height(resource._height),
    _data(std::move(resource._data))
{
}

Engine::TextureResource & Engine::TextureResource::operator = (
    const TextureResource & other
) noexcept {
    if (&other == this) {
        return *this;
    }
    _width = other._width;
    _height = other._height;
    _data = other._data;
    return *this;
}

Engine::TextureResource & Engine::TextureResource::operator = (
    TextureResource && other
) noexcept {
    if (&other == this) {
        return *this;
    }
    _width = other._width;
    _height = other._height;
    _data = std::move(other._data);
    return *this;
}

Engine::ResourceType Engine::TextureResource::getType() const noexcept
{
    return Engine::ResourceType::TextureType;
}

std::uint32_t Engine::TextureResource::getWidth() const noexcept
{
    return _width;
}

std::uint32_t Engine::TextureResource::getHeight() const noexcept
{
    return _height;
}

const std::vector<std::uint8_t> & Engine::TextureResource::getPixelArray() const noexcept
{
    return _data;
}
