#include "Engine/Core.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/Window.hpp"

#include <chrono>
#include <thread>

Engine::Core::Core(const std::string &name) : _gameName(name)
{
}

Engine::Core::~Core()
{
    if (_initialized)
    {
        delete _resourceManager;
    }
}

void Engine::Core::init() noexcept
{
    if (_initialized)
    {
        // TODO Log the double initialization
        return;
    }
    _resourceManager = new ResourceManager();
    _initialized = true;
    Window window = Window(_gameName, 1920, 1080);

    window.initWindow();

    Graphics graphic = Graphics(_gameName, std::make_shared<Engine::Window>(window));

    window.run();
}

void Engine::Core::run() noexcept
{
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

Engine::ResourceManager *Engine::Core::getResourceManager() noexcept
{
    return _resourceManager;
}
