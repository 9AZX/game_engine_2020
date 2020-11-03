#include "Core.hpp"
#include "Audio.hpp"

int main(void)
{
    Audio audio = Audio("sample.wav");

    audio.play();
    Core core = Core("Super jeu");

    core.init();
}
