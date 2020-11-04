#include "Graphics.hpp"

Graphics::Graphics(std::string _gameName, std::shared_ptr<Engine::Window> window) : _appName(_gameName), _window(window)
{

    gInstance = std::make_shared<Instance>(_gameName);
    gDevice = std::make_shared<Device>(gInstance);
    gSwapChain = std::make_shared<Swapchain>(_window, gInstance, gDevice);
}

Graphics::~Graphics()
{
}
