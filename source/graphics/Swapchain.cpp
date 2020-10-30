#include "Swapchain.hpp"

Swapchain::Swapchain(std::shared_ptr<EngineWindow> window, std::shared_ptr<Instance> instance) : _window(window), _instance(instance)
{
  vk::UniqueSurfaceKHR surface;
  {
    VkSurfaceKHR _surface;
    vk::ObjectDestroy<vk::Instance, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> _deleter(_instance->getInstance()->get());

    VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    surfaceCreateInfo.hinstance = _window->getHinstance();
    surfaceCreateInfo.hwnd = _window->getHwnd();
    surfaceCreateInfo.pNext = NULL;
    surfaceCreateInfo.flags = 0;
    VkResult result = vkCreateWin32SurfaceKHR(_instance->getInstance()->get(), &surfaceCreateInfo, nullptr, &_surface);
    if (result != VK_SUCCESS)
    {
      throw std::runtime_error("failed to create window surface!");
    }
    surface = vk::UniqueSurfaceKHR(vk::SurfaceKHR(_surface), _deleter);
  }
}

Swapchain::~Swapchain()
{
}
