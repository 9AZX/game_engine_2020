#include "Engine/Exceptions/GraphicsException.hpp"

Engine::GraphicsException::GraphicsException(std::string message):
    Exception(std::move(message))
{
}
