#pragma once

#ifndef Audio_HPP_
#define Audio_HPP_

#include <iostream>
#include <portaudio.h>

#include <stdio.h>
#include <string.h>
#include "sndfile.h"

#define FRAMES_PER_BUFFER   (512)

typedef struct
{
    SNDFILE* file;
    SF_INFO      info;
} callback_data_s;

static int callback(const void* input, void* output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData
);

class Audio
{
public:
    Audio(std::string file);

    void play();
    void stop();

private:
    int errorManager(PaStream* stream, callback_data_s data);
    const std::string _file = "";

protected:
 
   
}; /* class Audio */

#endif /* Audio_HPP_ */