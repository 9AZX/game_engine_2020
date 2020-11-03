#include "Core.hpp"
#include "EngineWindow.hpp"
#include "Audio.hpp"
#include <iostream>
#include <portaudio.h>


// Create crossplatform with GLFW or without
// TODO #4

Core::Core(std::string gameName) : _gameName(gameName)
{
}

void Core::init() const noexcept
{
    EngineWindow window = EngineWindow(_gameName, 1920, 1080);
    //Audio audio = Audio("sample.wav");

    //audio.play();
    window.initWindow();
    window.run();
}
