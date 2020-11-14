#ifndef ENGINE_EXCEPTIONS_FILE_EXCEPTION_HPP_
#define ENGINE_EXCEPTIONS_FILE_EXCEPTION_HPP_

#include "Engine/Exceptions/Exception.hpp"

namespace Engine {

class FileException: public Exception {
    public:
        FileException(std::string message);
}; /* class FileException */

} /* namespace Engine */

#endif /* ENGINE_EXCEPTIONS_FILE_EXCEPTION_HPP_ */
