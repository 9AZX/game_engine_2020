#ifndef Graphics_HPP_
#define Graphics_HPP_

#include <vulkan/vulkan.hpp>
#include "graphics/Instance.hpp"
#include "graphics/Device.hpp"
#include "graphics/Swapchain.hpp"

class Graphics
{
public:
    Graphics(std::string name, std::shared_ptr<EngineWindow> window);
    ~Graphics();

    Instance gInstance;
    Device gDevice;
    Swapchain gSwapChain;

private:
    std::string _appName;
#if !defined(NDEBUG)
    //TODO #8 Vulkan message debuging
#endif
};

#endif /* !Graphics_HPP_ */
