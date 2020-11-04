#ifndef SWAPCHAIN_HPP_
#define SWAPCHAIN_HPP_

#define VK_USE_PLATFORM_WIN32_KHR

#include <vulkan/vulkan.hpp>
#include "Engine/Window.hpp"
#include "graphics/Instance.hpp"
#include "graphics/Device.hpp"

class Swapchain
{
public:
    Swapchain(std::shared_ptr<Engine::Window> window, std::shared_ptr<Instance> instance, std::shared_ptr<Device> device);
    Swapchain() = default;
    ~Swapchain();

private:
    std::shared_ptr<Engine::Window> _window;
    std::shared_ptr<Instance> _instance;
    std::shared_ptr<Device> _device;
};

#endif /* !SWAPCHAIN_HPP_ */
