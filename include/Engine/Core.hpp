#ifndef ENGINE_CORE_HPP_
#define ENGINE_CORE_HPP_

#include "Engine/Resources/ResourceManager.hpp"

#include <string>

namespace Engine {

class Core {
    public:
        Core() = default;
        Core(const std::string & name);
        ~Core();

        void init() noexcept;
        void run() noexcept;

        ResourceManager * getResourceManager() noexcept;

    private:
        ResourceManager * _resourceManager;
        const std::string _gameName = "";
        bool _initialized = false;
}; /* class Core */

} /* namespace Engine */

#endif /* ENGINE_CORE_HPP_ */
