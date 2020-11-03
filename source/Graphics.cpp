#include "Graphics.hpp"

Graphics::Graphics(std::string _gameName, std::shared_ptr<EngineWindow> window) : _appName(_gameName), _window(window)
{

    gInstance = std::make_shared<Instance>(Instance(_gameName));
    gDevice = std::make_shared<Device>(Device(gInstance));
    gSwapChain = std::make_shared<Swapchain>(Swapchain(_window, gInstance, gDevice));
}

Graphics::~Graphics()
{
}
