#ifndef SWAPCHAIN_HPP_
#define SWAPCHAIN_HPP_

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan/vulkan.hpp>
#include "EngineWindow.hpp"
#include "graphics/Instance.hpp"

class Swapchain
{
public:
    Swapchain(std::shared_ptr<EngineWindow> window, std::shared_ptr<Instance> instance);
    Swapchain() = default;
    ~Swapchain();

private:
    std::shared_ptr<EngineWindow> _window;
    std::shared_ptr<Instance> _instance;
};

#endif /* !SWAPCHAIN_HPP_ */
