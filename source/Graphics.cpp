#include "Graphics.hpp"

Graphics::Graphics(std::string _gameName) : _appName(_gameName), gInstance(_gameName)
{
    gDevice = Device(std::make_shared<Instance>(gInstance));
}

Graphics::~Graphics()
{
}
