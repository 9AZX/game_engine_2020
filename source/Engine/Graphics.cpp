#include "Engine/Graphics.hpp"

std::shared_ptr<Engine::Graphics> Engine::Graphics::graphics = nullptr;

Engine::Graphics::Graphics(
    std::string _gameName,
    std::shared_ptr<Engine::Window> window,
    bool enableDebugging
):
    _appName(_gameName),
    _window(window),
    _enableDebugging(enableDebugging)
{

    gInstance = std::make_shared<Instance>(_gameName, _enableDebugging);
    messenger.init(gInstance);
    gDevice = std::make_shared<Device>(gInstance);
    gSwapChain = std::make_shared<Swapchain>(_window, gInstance, gDevice);
}

Engine::Graphics::~Graphics()
{
}

std::shared_ptr<Engine::Graphics> Engine::Graphics::getInstance()
{
    if (!graphics)
    {
        graphics = std::make_shared<Graphics>();
    }
    return graphics;
}

std::shared_ptr<Engine::Device> Engine::Graphics::getDevice()
{
    return gDevice;
}

std::shared_ptr<Engine::Swapchain> Engine::Graphics::getSwapchain()
{
    return gSwapChain;
}

std::shared_ptr<Renderpass> Engine::Graphics::getRenderpass()
{
    return gRenderpass;
}
