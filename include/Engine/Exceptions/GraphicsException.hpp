#ifndef ENGINE_GRAPHICS_EXCEPTION_HPP_
#define ENGINE_GRAPHICS_EXCEPTION_HPP_

#include "Engine/Exceptions/Exception.hpp"

namespace Engine {

class GraphicsException: public Exception {
    public:
        GraphicsException(std::string message);
}; /* class GraphicsException */

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_EXCEPTION_HPP_ */
