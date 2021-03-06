#include "Engine/Graphics/Swapchain.hpp"

#include "Engine/Utils.hpp"

Engine::Swapchain::Swapchain(std::shared_ptr<Engine::Window> window, std::shared_ptr<Instance> instance, std::shared_ptr<Device> device) : _window(window), _instance(instance), _device(device)
{
  VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
  surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  surfaceCreateInfo.hinstance = _window->getHinstance();
  surfaceCreateInfo.hwnd = _window->getHwnd();
  surfaceCreateInfo.pNext = NULL;
  surfaceCreateInfo.flags = 0;
  surface = _instance->getInstance()->get().createWin32SurfaceKHRUnique(surfaceCreateInfo);

  std::vector<vk::QueueFamilyProperties>
      queueFamilyProperties = _device->getPhysicalDevice().get()->getQueueFamilyProperties();

  size_t presentQueueFamilyIndex =
      _device->getPhysicalDevice().get()->getSurfaceSupportKHR(static_cast<uint32_t>(_device->graphicsQueueFamilyIndex), surface.get())
          ? _device->graphicsQueueFamilyIndex
          : queueFamilyProperties.size();
  if (presentQueueFamilyIndex == queueFamilyProperties.size())
  {
    for (size_t i = 0; i < queueFamilyProperties.size(); i++)
    {
      if ((queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) &&
          _device->getPhysicalDevice().get()->getSurfaceSupportKHR(static_cast<uint32_t>(i), surface.get()))
      {
        _device->graphicsQueueFamilyIndex = checked_cast<uint32_t>(i);
        presentQueueFamilyIndex = i;
        break;
      }
    }
    if (_device->graphicsQueueFamilyIndex == queueFamilyProperties.size())
    {
      for (size_t i = 0; i < queueFamilyProperties.size(); i++)
      {
        if (_device->getPhysicalDevice().get()->getSurfaceSupportKHR(static_cast<uint32_t>(i), surface.get()))
        {
          presentQueueFamilyIndex = i;
          break;
        }
      }
    }
  }
  if ((_device->graphicsQueueFamilyIndex == queueFamilyProperties.size()) ||
      (presentQueueFamilyIndex == queueFamilyProperties.size()))
  {
    throw std::runtime_error("Could not find a queue for graphics or present -> terminating");
  }

  // create a device
  _device->createUniqueDevice();

  std::vector<vk::SurfaceFormatKHR> formats = _device->getPhysicalDevice().get()->getSurfaceFormatsKHR(surface.get());
  assert(!formats.empty());
  swapChainImageFormat =
      (formats[0].format == vk::Format::eUndefined) ? vk::Format::eB8G8R8A8Unorm : formats[0].format;

  vk::SurfaceCapabilitiesKHR surfaceCapabilities = _device->getPhysicalDevice().get()->getSurfaceCapabilitiesKHR(surface.get());
  VkExtent2D swapchainExtent;

  swapchainExtent = surfaceCapabilities.currentExtent;

  vk::PresentModeKHR swapchainPresentMode = vk::PresentModeKHR::eFifo;

  vk::SurfaceTransformFlagBitsKHR preTransform =
      (surfaceCapabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity)
          ? vk::SurfaceTransformFlagBitsKHR::eIdentity
          : surfaceCapabilities.currentTransform;

  vk::CompositeAlphaFlagBitsKHR compositeAlpha =
      (surfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied)
          ? vk::CompositeAlphaFlagBitsKHR::ePreMultiplied
          : (surfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied)
                ? vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
                : (surfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::eInherit)
                      ? vk::CompositeAlphaFlagBitsKHR::eInherit
                      : vk::CompositeAlphaFlagBitsKHR::eOpaque;

  vk::SwapchainCreateInfoKHR swapChainCreateInfo(vk::SwapchainCreateFlagsKHR(),
                                                 surface.get(),
                                                 surfaceCapabilities.minImageCount,
                                                 swapChainImageFormat,
                                                 vk::ColorSpaceKHR::eSrgbNonlinear,
                                                 swapchainExtent,
                                                 1,
                                                 vk::ImageUsageFlagBits::eColorAttachment,
                                                 vk::SharingMode::eExclusive,
                                                 {},
                                                 preTransform,
                                                 compositeAlpha,
                                                 swapchainPresentMode,
                                                 true,
                                                 nullptr);

  uint32_t queueFamilyIndices[2] = {static_cast<uint32_t>(_device->graphicsQueueFamilyIndex),
                                    static_cast<uint32_t>(presentQueueFamilyIndex)};
  if (_device->graphicsQueueFamilyIndex != presentQueueFamilyIndex)
  {
    swapChainCreateInfo.imageSharingMode = vk::SharingMode::eConcurrent;
    swapChainCreateInfo.queueFamilyIndexCount = 2;
    swapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
  }
  else
  {
    swapChainCreateInfo.imageSharingMode = vk::SharingMode::eExclusive;
    swapChainCreateInfo.queueFamilyIndexCount = 0;
    swapChainCreateInfo.pQueueFamilyIndices = nullptr;
  }

  swapchain = _device->getUniqueDevice()->get().createSwapchainKHRUnique(swapChainCreateInfo);

  swapChainImages = _device->getUniqueDevice()->get().getSwapchainImagesKHR(swapchain.get());

  imageViews.reserve(swapChainImages.size());
  vk::ComponentMapping componentMapping(
      vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA);
  vk::ImageSubresourceRange subResourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1);
  for (auto image : swapChainImages)
  {
    vk::ImageViewCreateInfo imageViewCreateInfo(
        vk::ImageViewCreateFlags(), image, vk::ImageViewType::e2D, swapChainImageFormat, componentMapping, subResourceRange);
    imageViews.push_back(_device->getUniqueDevice()->get().createImageViewUnique(imageViewCreateInfo));
  }
  this->swapChainImageExtent = swapchainExtent;
}

Engine::Swapchain::~Swapchain()
{
}
