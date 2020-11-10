#include "Engine/Logging/ConsoleSink.hpp"

Engine::Logging::ConsoleSink::ConsoleSink(std::ostream & out):
    _out(out)
{
}

void Engine::Logging::ConsoleSink::log(const std::string & message)
{
    _out << message << std::endl;
}
