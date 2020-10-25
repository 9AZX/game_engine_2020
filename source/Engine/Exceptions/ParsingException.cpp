#include "Engine/Exceptions/ParsingException.hpp"

Engine::ParsingException::ParsingException(std::string message):
    Exception(message)
{
}
