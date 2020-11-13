#include "Engine/Core.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/Logging/ConsoleSink.hpp"
#include "Engine/Window.hpp"

#include <iostream>

std::shared_ptr<Engine::Logging::Logger> Engine::Core::_logger = nullptr;

Engine::Core::Core(const std::string &name) : _gameName(name)
{
}

void Engine::Core::init() noexcept
{
    if (_initialized)
    {
        _logger->log(
            Logging::Level::Warning,
            "Tried to initialize the core another time"
        );
        return;
    }
    _initialized = true;

    _logger = std::make_shared<Logging::Logger>();
    _logger->createSink<Logging::ConsoleSink>("console-sink", true, std::cout);
    _logger->log(Logging::Level::Info, "Initializing core");

    _resourceManager = std::make_shared<ResourceManager>();

    _window = std::make_shared<Window>(_gameName, 1920, 1080);
    _window->initWindow();

    _graphics = std::make_shared<Graphics>(_gameName, _window);
}

void Engine::Core::run() noexcept
{
    _window->run();
}

std::shared_ptr<Engine::ResourceManager> Engine::Core::getResourceManager() noexcept
{
    return _resourceManager;
}

std::shared_ptr<Engine::Logging::Logger> Engine::Core::getLogger() noexcept
{
    return _logger;
}
