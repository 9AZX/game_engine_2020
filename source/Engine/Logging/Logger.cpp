#include "Engine/Logging/Logger.hpp"

Engine::Logging::Logger::Logger():
    _begin(std::chrono::high_resolution_clock::now())
{
    #ifdef NDEBUG
    _enabledLevels[Level::Debug] = false;
    #else
    _enabledLevels[Level::Debug] = true;
    #endif

    _enabledLevels[Level::Error] = true;
    _enabledLevels[Level::Fatal] = true;
    _enabledLevels[Level::Info] = true;
    _enabledLevels[Level::Warning] = true;
    _enabledLevels[Level::MAX_VALUE] = false;
}

void Engine::Logging::Logger::enableLevel(Level level) noexcept
{
    _enabledLevels[level] = true;
}

void Engine::Logging::Logger::disableLevel(Level level) noexcept
{
    _enabledLevels[level] = false;
}

void Engine::Logging::Logger::enableSinkLevel(
    const std::string & name,
    Level level
) noexcept {
    auto sink = _sinks.find(name);

    if (sink != _sinks.end()) {
        sink->second->enableLevel(level);
    }
}

void Engine::Logging::Logger::disableSinkLevel(
    const std::string & name,
    Level level
) noexcept {
    auto sink = _sinks.find(name);

    if (sink != _sinks.end()) {
        sink->second->disableLevel(level);
    }
}

bool Engine::Logging::Logger::addSink(
    const std::string & name,
    bool copyLoggerLevels,
    std::unique_ptr<Sink> sink
) noexcept {
    if (_sinks.find(name) == _sinks.end()) {
        _sinks.emplace(name, std::move(sink));
        if (copyLoggerLevels) {
            _sinks[name]->setLevels(_enabledLevels);
        }
        return true;
    }
    return false;
}

void Engine::Logging::Logger::removeSink(const std::string & name) noexcept
{
    _sinks.erase(name);
}
