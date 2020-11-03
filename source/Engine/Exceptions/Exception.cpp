#include "Engine/Exceptions/Exception.hpp"

Engine::Exception::Exception(std::string message):
    _message(message)
{
}

const char * Engine::Exception::what() const noexcept
{
    return _message.c_str();
}
