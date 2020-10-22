#ifndef ENGINE_EXCEPTION_PARSING_EXCEPTION_HPP_
#define ENGINE_EXCEPTION_PARSING_EXCEPTION_HPP_

#include "Engine/Exception/Exception.hpp"

namespace Engine {

class ParsingException: public Exception {
    public:
        ParsingException(std::string message);
}; /* class ParsingException */

} /* namespace Engine */

#endif /* ENGINE_EXCEPTION_PARSING_EXCEPTION_HPP_ */
