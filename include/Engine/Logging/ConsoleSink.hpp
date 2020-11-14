#ifndef ENGINE_LOGGING_CONSOLE_SINK_HPP_
#define ENGINE_LOGGING_CONSOLE_SINK_HPP_

#include "Engine/Logging/Sink.hpp"

#include <ostream>

namespace Engine {

namespace Logging {

class ConsoleSink: public Sink {
    public:
        ConsoleSink() = delete;
        ConsoleSink(std::ostream & out);

        void log(const std::string & message) override;

    private:
        std::ostream & _out;
}; /* class ConsoleSink */

} /* namespace Logging */

} /* namespace Engine */

#endif /* ENGINE_LOGGING_CONSOLE_SINK_HPP_ */
