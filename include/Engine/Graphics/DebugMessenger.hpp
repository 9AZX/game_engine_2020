#ifndef ENGINE_GRAPHICS_DEBUG_MESSENGER_HPP_
#define ENGINE_GRAPHICS_DEBUG_MESSENGER_HPP_

#include "Engine/Graphics/Instance.hpp"

#include <vulkan/vulkan.hpp>

namespace Engine {

class DebugMessenger {
    public:
        DebugMessenger() = default;
        ~DebugMessenger() = default;

        void init(std::shared_ptr<Instance> instance);

        static vk::DebugUtilsMessengerCreateInfoEXT getCreateInfo() noexcept;

    private:
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugMessageCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageTypes,
            const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
            void *
        );

        vk::UniqueDebugUtilsMessengerEXT _debugUtilsMessenger;
}; /* class DebugMessenger */

} /* namespace Engine */

#endif /* ENGINE_GRAPHICS_DEBUG_MESSENGER_HPP_ */
