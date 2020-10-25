#ifndef ENGINE_EXCEPTIONS_EXCEPTION_HPP_
#define ENGINE_EXCEPTIONS_EXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace Engine {

class Exception: public std::exception {
    public:
        Exception(std::string message);

        const char * what() const noexcept override;

    private:
        std::string _message;
}; /* class Exception */

} /* namespace Engine */

#endif /* ENGINE_EXCEPTIONS_EXCEPTION_HPP_ */
