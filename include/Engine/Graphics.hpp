#ifndef ENGINE_GRAPHICS_HPP_
#define ENGINE_GRAPHICS_HPP_

#include "Engine/Graphics/DebugMessenger.hpp"
#include "Engine/Graphics/Device.hpp"
#include "Engine/Graphics/Instance.hpp"
#include "Engine/Graphics/Swapchain.hpp"

#include <vulkan/vulkan.hpp>

namespace Engine {

class Graphics
{
public:
    Graphics(std::string name, std::shared_ptr<Engine::Window> window);
    Graphics() {}
    Graphics(
        std::string name,
        std::shared_ptr<Engine::Window> window,
        bool enableDebugging
    );
    ~Graphics();

    std::shared_ptr<Instance> gInstance;
    std::shared_ptr<Device> gDevice;
    std::shared_ptr<Swapchain> gSwapChain;
    DebugMessenger messenger;

    static std::shared_ptr<Graphics> graphics;

    static std::shared_ptr<Graphics> getInstance()
    {
        if (!graphics)
        {
            graphics = std::make_shared<Graphics>();
        }
        return graphics;
    }

    std::shared_ptr<Device> getDevice()
    {
        return gDevice;
    }

    std::shared_ptr<Swapchain> getSwapchain()
    {
        return gSwapChain;
    }

    vk::UniqueCommandBuffer getCurrentCommandBuffer()
    {
        return currentCommandBuffer;
    }

private:
    bool _enableDebugging;
    std::string _appName;

    std::shared_ptr<Engine::Window> _window;
    vk::UniqueCommandBuffer currentCommandBuffer;


#if !defined(NDEBUG)
    //TODO #8 Vulkan message debuging
#endif
}; /* class Graphics */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_HPP_ */
