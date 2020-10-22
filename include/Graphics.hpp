#ifndef Graphics_HPP_
#define Graphics_HPP_

#include <vulkan/vulkan.hpp>
#include "graphics/Instance.hpp"

class Graphics
{
public:
    Graphics(std::string);
    ~Graphics();

private:
    std::string _appName;
    Instance _instance;
};

#endif /* !Graphics_HPP_ */
