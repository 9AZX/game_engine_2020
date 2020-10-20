#include "Core.hpp"
#include "EngineWindow.hpp"

#include <iostream>
#include <portaudio.h>

// Create crossplatform with GLFW or without
// TODO #4

void Core::init() const noexcept
{
    EngineWindow window = EngineWindow("3D Game Engine", 1920, 1080);

    window.initWindow();
    window.run();

    PaError err = Pa_Initialize();

    if (err != paNoError)
    {
        std::cerr << "Could not initialize portaudio" << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_Terminate();
    if (err != paNoError)
    {
        std::cerr << "Could not terminate portaudio" << Pa_GetErrorText(err) << std::endl;
    }
}
