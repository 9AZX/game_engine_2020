#ifndef ENGINE_CORE_HPP_
#define ENGINE_CORE_HPP_

#include "Engine/Graphics.hpp"
#include "Engine/Resources/ResourceManager.hpp"
#include "Engine/Window.hpp"

#include <memory>
#include <string>

namespace Engine {

class Core {
    public:
        Core() = default;
        Core(const std::string & name);
        ~Core() = default;

        void init() noexcept;
        void run() noexcept;

        std::shared_ptr<ResourceManager> getResourceManager() noexcept;

    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<ResourceManager> _resourceManager;
        std::shared_ptr<Graphics> _graphics;
        const std::string _gameName = "";
        bool _initialized = false;
}; /* class Core */

} /* namespace Engine */

#endif /* ENGINE_CORE_HPP_ */
