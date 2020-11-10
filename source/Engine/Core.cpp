#include "Engine/Core.hpp"

#include "Engine/Graphics.hpp"
#include "Engine/Window.hpp"

Engine::Core::Core(const std::string &name) : _gameName(name)
{
}

void Engine::Core::init() noexcept
{
    if (_initialized)
    {
        // TODO Log the double initialization
        return;
    }
    _initialized = true;
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
