#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <string>

class Engine {
    public:
        Engine(const std::string & message);

        void sayHello() const noexcept;

    private:
        std::string _message;
}; /* class Engine */

#endif /* ENGINE_HPP_ */
