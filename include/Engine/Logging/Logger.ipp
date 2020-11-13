#ifndef ENGINE_LOGGING_LOGGER_IPP_
#define ENGINE_LOGGING_LOGGER_IPP_

#include <fmt/core.h>

template <typename T, typename ... Args>
bool Engine::Logging::Logger::createSink(
    const std::string & name,
    bool copyLoggerLevels,
    Args && ... args
) noexcept {
    if (_sinks.find(name) == _sinks.end()) {
        _sinks.emplace(name, std::make_unique<T>(std::forward<Args>(args)...));
        if (copyLoggerLevels) {
            _sinks[name]->setLevels(_enabledLevels);
        }
        return true;
    }
    return false;
}

template <typename ... Args>
void Engine::Logging::Logger::log(
    Level level,
    const std::string & format,
    Args && ... args
) {
    if (_enabledLevels[level]) {
        std::chrono::time_point<std::chrono::high_resolution_clock> now
            = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - _begin
        );
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
            elapsedTime
        );
        elapsedTime -= std::chrono::duration_cast<std::chrono::milliseconds>(
            seconds
        );
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(
            seconds
        );
        seconds -= std::chrono::duration_cast<std::chrono::seconds>(
            minutes
        );

        std::string message;

        for (auto & pair: _sinks) {
            if (pair.second->isLevelEnabled(level)) {
                if (message.empty()) {
                    message = fmt::format(
                        "[{:02}:{:02}:{:03}][{}]" + format,
                        minutes.count(),
                        seconds.count(),
                        elapsedTime.count(),
                        levelNames[level],
                        std::forward<Args>(args)...
                    );
                }
                pair.second->log(message);
            }
        }
    }
}

#endif /* ENGINE_LOGGING_LOGGER_IPP_ */
