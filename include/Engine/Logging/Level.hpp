#ifndef ENGINE_LOGGING_LEVEL_HPP_
#define ENGINE_LOGGING_LEVEL_HPP_

#include <array>
#include <string>

namespace Engine {

namespace Logging {

enum Level {
    Debug,
    Error,
    Fatal,
    Info,
    Warning,
    MAX_VALUE
};

const std::array<std::string, Level::MAX_VALUE + 1> levelNames {
    "DEBUG",
    "ERROR",
    "FATAL",
    "INFO",
    "WARNING",
    "MAX_VALUE"
};

} /* namespace Logging */

} /* namespace Engine */

#endif /* ENGINE_LOGGING_LEVEL_HPP_ */
