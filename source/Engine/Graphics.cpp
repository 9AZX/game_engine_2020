#include "Engine/Graphics.hpp"

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
