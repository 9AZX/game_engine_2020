#include "Core.hpp"
#include "EngineWindow.hpp"

#include <iostream>
#include <portaudio.h>

// For Debuging or crossplatform with GLFW
// TODO #4
void Core::init() const noexcept
{
    EngineWindow window = EngineWindow();

    window.initWindow();
    window.run();
    PaError err = Pa_Initialize();
}

// For WINDOWS ONLY
void Core::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) const noexcept
{
    EngineWindow window = EngineWindow(hInstance, hPrevInstance, pCmdLine, nCmdShow);

    window.initWindow();
    window.run();

    // Resources manager
    //TODO #3

    // Audio init
    // TODO #2
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
