#ifndef ENGINE_EXCEPTIONS_PARSING_EXCEPTION_HPP_
#define ENGINE_EXCEPTIONS_PARSING_EXCEPTION_HPP_

#include "Engine/Exceptions/Exception.hpp"

namespace Engine {

class ParsingException: public Exception {
    public:
        ParsingException(std::string message);
}; /* class ParsingException */

} /* namespace Engine */

#endif /* ENGINE_EXCEPTIONS_PARSING_EXCEPTION_HPP_ */
