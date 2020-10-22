#ifndef Graphics_HPP_
#define Graphics_HPP_

#include <vulkan/vulkan.hpp>
#include "graphics/Instance.hpp"

class Graphics
{
public:
    Graphics(std::string);
    ~Graphics();

    Instance gInstance;

private:
    std::string _appName;
#if !defined(NDEBUG)
    //TODO #8 Vulkan message debuging
#endif
};

#endif /* !Graphics_HPP_ */
