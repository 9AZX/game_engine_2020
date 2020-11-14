#ifndef ENGINE_LOGGING_SINK_HPP_
#define ENGINE_LOGGING_SINK_HPP_

#include "Engine/Logging/Level.hpp"

#include <array>
#include <string>

namespace Engine {

namespace Logging {

class Sink {
    public:
        Sink();
        virtual ~Sink() = default;

        void enableLevel(Level level) noexcept;
        void disableLevel(Level level) noexcept;
        bool isLevelEnabled(Level level) noexcept;
        void setLevels(
            const std::array<bool, Level::MAX_VALUE + 1> & levels
        ) noexcept;
        virtual void log(const std::string & message) = 0;

    private:
        std::array<bool, Level::MAX_VALUE + 1> _enabledLevels;
}; /* class Sink */

} /* namespace Logging */

} /* namespace Engine */

#endif /* ENGINE_LOGGING_SINK_HPP_ */
