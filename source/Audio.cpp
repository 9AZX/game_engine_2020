#include "Audio.hpp"

Audio::Audio(std::string file) : _file(file)
{
    printf("init %s", _file.c_str());
}

void Audio::play()
{
    printf("play");
    
    PaStream* stream;
    callback_data_s data;
    

   
    /* Open the soundfile */
    
    data.file = sf_open(_file.c_str(), SFM_READ, &data.info);
    
    if (sf_error(data.file) != SF_ERR_NO_ERROR)
    {
        fprintf(stderr, "%s\n", sf_strerror(data.file));
        fprintf(stderr, "File: %s\n", _file.c_str());
        return;
    }
    
    /* init portaudio */
    if (errorManager(&stream, data) == 0);
}

void Audio::stop()
{
    printf("stop");
}

int Audio::errorManager(PaStream* stream, callback_data_s data)
{
    
    PaError error;

    error = Pa_Initialize();
    if (error != paNoError)
    {
        fprintf(stderr, "Problem initializing\n");
        return 1;
    }

    error = Pa_OpenDefaultStream(&stream, 0, data.info.channels,
        paFloat32, data.info.samplerate, FRAMES_PER_BUFFER, callback, &data);
    if (error != paNoError)
    {
        fprintf(stderr, "Problem opening Default Stream\n");
        return 1;
    }

    
    error = Pa_StartStream(stream);
    if (error != paNoError)
    {
        fprintf(stderr, "Problem opening starting Stream\n");
        return 1;
    }

    while (Pa_IsStreamActive(stream))
    {
        Pa_Sleep(100);
    }

    sf_close(data.file);

    
    error = Pa_CloseStream(stream);
    if (error != paNoError)
    {
        fprintf(stderr, "Problem closing stream\n");
        return 1;
    }

    error = Pa_Terminate();
    if (error != paNoError)
    {
        fprintf(stderr, "Problem terminating\n");
        return 1;
    }

    
    return 0;
}

static int callback(const void* input, void* output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData
)
{
    
    float* out;
    callback_data_s* p_data = (callback_data_s*)userData;
    sf_count_t       num_read;

    out = (float*)output;
    p_data = (callback_data_s*)userData;
    
    /* clear output buffer */
    memset(out, 0, sizeof(float) * frameCount * p_data->info.channels);

    /* read directly into output buffer */
    num_read = sf_read_float(p_data->file, out, frameCount * p_data->info.channels);

    /*  If we couldn't read a full frameCount of samples we've reached EOF */
    
    if (num_read < frameCount)
    {
        return paComplete;
    }
    
    return paContinue;
}