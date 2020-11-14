#ifndef ENGINE_LOGGING_LOGGER_HPP_
#define ENGINE_LOGGING_LOGGER_HPP_

#include "Engine/Logging/Level.hpp"
#include "Engine/Logging/Sink.hpp"

#include <array>
#include <chrono>
#include <map>
#include <memory>
#include <string>

namespace Engine {

namespace Logging {

class Logger {
    public:
        Logger();

        void enableLevel(Level level) noexcept;
        void disableLevel(Level level) noexcept;
        void enableSinkLevel(const std::string & name, Level level) noexcept;
        void disableSinkLevel(const std::string & name, Level level) noexcept;

        template <typename T, typename ... Args>
        bool createSink(
            const std::string & name,
            bool copyLevels,
            Args && ... args
        ) noexcept;
        bool addSink(
            const std::string & name,
            bool copyLevels,
            std::unique_ptr<Sink> sink
        ) noexcept;
        void removeSink(const std::string & name) noexcept;

        template <typename ... Args>
        void log(Level level, const std::string & format, Args && ... args);

    private:
        std::map<std::string, std::unique_ptr<Sink>> _sinks;
        std::chrono::time_point<std::chrono::high_resolution_clock> _begin;
        std::array<bool, Level::MAX_VALUE + 1> _enabledLevels;
}; /* class Logger */

} /* namespace Logging */

} /* namespace Engine */

#include "Engine/Logging/Logger.ipp"

#endif /* ENGINE_LOGGING_LOGGER_HPP_ */
