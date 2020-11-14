#include "Engine/Graphics/DebugMessenger.hpp"

#include "Engine/Core.hpp"
#include "Engine/Exceptions/GraphicsException.hpp"
#include "Engine/Logging/Logger.hpp"

static PFN_vkCreateDebugUtilsMessengerEXT pfnVkCreateDebugUtilsMessengerEXT {};
static PFN_vkDestroyDebugUtilsMessengerEXT pfnVkDestroyDebugUtilsMessengerEXT {};

void Engine::DebugMessenger::init(std::shared_ptr<Instance> instance)
{
    pfnVkCreateDebugUtilsMessengerEXT
        = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            instance->getInstance()->get().getProcAddr(
                "vkCreateDebugUtilsMessengerEXT"
            )
        );
    pfnVkDestroyDebugUtilsMessengerEXT
        = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            instance->getInstance()->get().getProcAddr(
                "vkDestroyDebugUtilsMessengerEXT"
            )
        );

    if (!pfnVkCreateDebugUtilsMessengerEXT
        || !pfnVkDestroyDebugUtilsMessengerEXT) {
        throw GraphicsException("could not initialize the debug messenger");
    }
    _debugUtilsMessenger
        = instance->getInstance()->get().createDebugUtilsMessengerEXTUnique(
            getCreateInfo()
        );
}

vk::DebugUtilsMessengerCreateInfoEXT Engine::DebugMessenger::getCreateInfo() noexcept
{
    vk::DebugUtilsMessageSeverityFlagsEXT severityFlags(
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
    );

    vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
        | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
        | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
    );

    return vk::DebugUtilsMessengerCreateInfoEXT(
        {},
        severityFlags,
        messageTypeFlags,
        debugMessageCallback
    );
}

VKAPI_ATTR VkBool32 VKAPI_CALL Engine::DebugMessenger::debugMessageCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
    void *
) {
    vk::DebugUtilsMessageSeverityFlagBitsEXT severity
        = static_cast<vk::DebugUtilsMessageSeverityFlagBitsEXT>(messageSeverity);
    Logging::Level loggingLevel;

    if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eError) {
        loggingLevel = Logging::Level::Error;
    } else if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
        loggingLevel = Logging::Level::Warning;
    } else if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo) {
        loggingLevel = Logging::Level::Info;
    } else if (severity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose) {
        loggingLevel = Logging::Level::Debug;
    }
    Core::getLogger()->log(
        loggingLevel,
        "[Graphics] {} {} {} {}",
        vk::to_string(static_cast<vk::DebugUtilsMessageTypeFlagsEXT>(messageTypes)),
        pCallbackData->pMessageIdName,
        pCallbackData->messageIdNumber,
        pCallbackData->pMessage
    );
    return true;
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo,
    const VkAllocationCallbacks * pAllocator,
    VkDebugUtilsMessengerEXT * pMessenger
) {
    return pfnVkCreateDebugUtilsMessengerEXT(
        instance,
        pCreateInfo,
        pAllocator,
        pMessenger
    );
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT messenger,
    const VkAllocationCallbacks * pAllocator
) {
    return pfnVkDestroyDebugUtilsMessengerEXT(
        instance,
        messenger,
        pAllocator
    );
}
