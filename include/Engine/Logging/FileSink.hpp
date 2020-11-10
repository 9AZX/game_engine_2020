#ifndef ENGINE_LOGGING_FILE_SINK_HPP_
#define ENGINE_LOGGING_FILE_SINK_HPP_

#include "Engine/Logging/Sink.hpp"

#include <filesystem>
#include <fstream>

namespace Engine {

namespace Logging {

class FileSink: public Sink {
    public:
        FileSink() = default;

        void setFile(const std::filesystem::path & path);
        void log(const std::string & message) override;

    public:
        std::ofstream _file;
}; /* class FileSink */

} /* namespace Logging */

} /* namespace Engine */


#endif /* ENGINE_LOGGING_FILE_SINK_HPP_ */
