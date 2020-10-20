#include "Engine/Core.hpp"

#include <chrono>
#include <thread>

Engine::Core::~Core()
{
    if (_initialized) {
        delete _resourceManager;
    }
}

void Engine::Core::init() noexcept
{
    if (_initialized) {
        // TODO Log the double initialization
        return;
    }
    _resourceManager = new ResourceManager();
    _initialized = true;
}

void Engine::Core::run() noexcept
{
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

Engine::ResourceManager * Engine::Core::getResourceManager() noexcept
{
    return _resourceManager;
}
