#include "Core.hpp"
#include "EngineWindow.hpp"
#include "Graphics.hpp"

#include <iostream>
#include <portaudio.h>

// Create crossplatform with GLFW or without
// TODO #4

Core::Core(std::string gameName) : _gameName(gameName)
{
}

void Core::init() const noexcept
{
    try
    {
        EngineWindow window = EngineWindow(_gameName, 1920, 1080);
        window.initWindow();

        Graphics graphic = Graphics(_gameName, std::make_shared<EngineWindow>(window));

        window.run();
    }
    catch (vk::SystemError &err)
    {
        std::cout << "vk::SystemError: " << err.what() << std::endl;
        exit(-1);
    }
    catch (std::exception &err)
    {
        std::cout << "std::exception: " << err.what() << std::endl;
        exit(-1);
    }
    catch (...)
    {
        std::cout << "unknown error\n";
        exit(-1);
    }
}
