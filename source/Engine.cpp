#include "Engine.hpp"

#include <iostream>
#include <portaudio.h>

void Engine::init() const noexcept
{
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Could not initialize portaudio" << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "Could not terminate portaudio" << Pa_GetErrorText(err) << std::endl;
    }
}
