#include "Graphics.hpp"

Graphics::Graphics(std::string _gameName, std::shared_ptr<EngineWindow> window) : _appName(_gameName), gInstance(_gameName), gDevice(Device(std::make_shared<Instance>(gInstance))),
                                                                                  gSwapChain(Swapchain(window, std::make_shared<Instance>(gInstance)))
{
}

Graphics::~Graphics()
{
}
