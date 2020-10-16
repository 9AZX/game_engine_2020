#include "Engine.hpp"

#include <iostream>

Engine::Engine(const std::string & message):
    _message(message)
{
}

void Engine::sayHello() const noexcept
{
    std::cout << "Hello " << _message << std::endl;
}
