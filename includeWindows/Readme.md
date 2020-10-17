1-Si vous êtes sur visual studio, il faut configurer le projet sous le système windows pour pouvoir utiliser l'API win32
cliquez Projet -> propriétés du projet-> éditeur de liens -> Système -> Sous-Système -> Windows(\SUBSYSTEM:WINDOWS)

2-Remplacer le main() par:
  int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow)


3-Pour intégrer Vulkan dans la fenêtre windows avec Core.hpp, vous devez créer la surface de cette manière par rapport au tuto pour glfw:

VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
        surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.hinstance = core->getHinstance();
        surfaceCreateInfo.hwnd = core->getHwnd();
        surfaceCreateInfo.pNext = NULL;
        surfaceCreateInfo.flags = 0;
        if (int result = vkCreateWin32SurfaceKHR(instance, &surfaceCreateInfo, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }


4-Lorsque vous récupérez vos extensions pour créer votre instance avec auto extensions = getRequiredExtensions(), rajoutez à la ligne suivante:
    extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);


5-Dans cette fonction getRequiredExtensions() remplacez:
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    Par:
        std::vector<const char*> extensions = { VK_KHR_SURFACE_EXTENSION_NAME };


6-Dans les fonction chooseSwapExtent et recreateSwapChain, remplacez:
    glfwGetFramebufferSize(window, &width, &height) 

    et
    
    glfwGetFramebufferSize(window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(window, &width, &height);
        glfwWaitEvents();
    }

    Par:
        width = WIDTH;
        height = HEIGHT;