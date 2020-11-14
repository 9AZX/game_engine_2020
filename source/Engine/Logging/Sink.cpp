#include "Engine/Logging/Sink.hpp"

Engine::Logging::Sink::Sink()
{
    _enabledLevels[Level::Debug] = false;
    _enabledLevels[Level::Error] = false;
    _enabledLevels[Level::Fatal] = false;
    _enabledLevels[Level::Info] = false;
    _enabledLevels[Level::Warning] = false;
    _enabledLevels[Level::MAX_VALUE] = false;
}

void Engine::Logging::Sink::enableLevel(Level level) noexcept
{
    _enabledLevels[level] = true;
}

void Engine::Logging::Sink::disableLevel(Level level) noexcept
{
    _enabledLevels[level] = false;
}

bool Engine::Logging::Sink::isLevelEnabled(Level level) noexcept
{
    return _enabledLevels[level];
}

void Engine::Logging::Sink::setLevels(
    const std::array<bool, Level::MAX_VALUE + 1> & levels
) noexcept {
    _enabledLevels = levels;
}
