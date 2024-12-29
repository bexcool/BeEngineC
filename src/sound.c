#include "sound.h"

#include "SDL.h"
#include "SDL_mixer.h"
#include "logger.h"

int sound_init() {
    LOG("Initializing sound engine...");

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        LOG_E("Sound engine: Could not initialize SDL audio: %s\n", SDL_GetError());
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Sound engine: Could not initialize SDL mixer! SDL mixer error: %s\n", SDL_GetError());
        return 1;
    }

    Mix_ChannelFinished(_sound_channelFinished);

    LOG("Sound engine initialized.");
    return 0;
}

void sound_play2D(const char* path, int loops) {
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if (sound == NULL) {
        LOG_E("Sound engine: Could not load sound: %s\n", SDL_GetError());
        return;
    }

    if (Mix_PlayChannel(-1, sound, loops) < 0) {
        LOG_E("Sound engine: Could not play sound: %s\n", SDL_GetError());
        return;
    }
}

void _sound_channelFinished(int channel) {
    Mix_Chunk* sound = Mix_GetChunk(channel);
    if (sound != NULL) {
        Mix_FreeChunk(sound);
    }
}