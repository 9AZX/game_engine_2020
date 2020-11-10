#include "Engine/Exceptions/FileException.hpp"

Engine::FileException::FileException(std::string message):
    Exception(std::move(message))
{
}
