#ifndef ENGINE_GRAPHICS_HPP_
#define ENGINE_GRAPHICS_HPP_

#include "Engine/Graphics/Device.hpp"
#include "Engine/Graphics/Instance.hpp"
#include "Engine/Graphics/Swapchain.hpp"

#include <vulkan/vulkan.hpp>

namespace Engine {

class Graphics
{
public:
    Graphics(std::string name, std::shared_ptr<Engine::Window> window);
    ~Graphics();

    std::shared_ptr<Instance> gInstance;
    std::shared_ptr<Device> gDevice;
    std::shared_ptr<Swapchain> gSwapChain;

private:
    std::string _appName;

    std::shared_ptr<Engine::Window> _window;
#if !defined(NDEBUG)
    //TODO #8 Vulkan message debuging
#endif
}; /* class Graphics */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_HPP_ */
