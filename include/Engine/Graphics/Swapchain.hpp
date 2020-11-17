#ifndef ENGINE_GRAPHICS_SWAPCHAIN_HPP_
#define ENGINE_GRAPHICS_SWAPCHAIN_HPP_

#define VK_USE_PLATFORM_WIN32_KHR

#include "Engine/Graphics/Device.hpp"
#include "Engine/Graphics/Instance.hpp"
#include "Engine/Window.hpp"

#include <vulkan/vulkan.hpp>

namespace Engine
{

    class Swapchain
    {
    public:
        Swapchain(std::shared_ptr<Engine::Window> window, std::shared_ptr<Instance> instance, std::shared_ptr<Device> device);
        Swapchain() = default;
        ~Swapchain();

        vk::UniqueSwapchainKHR swapchain;
        vk::Format swapChainImageFormat;
        vk::Extent2D swapChainImageExtent;
        std::vector<vk::Image> swapChainImages;
        std::vector<vk::UniqueImageView> imageViews;
        vk::UniqueSurfaceKHR surface;

    private:
        std::shared_ptr<Engine::Window> _window;
        std::shared_ptr<Instance> _instance;
        std::shared_ptr<Device> _device;
    }; /* class Swapchain */

} /* namespace Engine */

#endif /* !ENGINE_GRAPHICS_SWAPCHAIN_HPP_ */
