#define MINIAUDIO_IMPLEMENTATION
#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() : musicInitialized(false), engineInitialized(false) {}

AudioManager::~AudioManager() {

}

AudioManager& AudioManager::instance() {
    static AudioManager audioManager;
    return audioManager;
}

void AudioManager::init() {
    if (engineInitialized) {
        return;
    }
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "[AudioManager] Error al inicializar el motor de audio." << std::endl;
    }
    else {
        std::cout << "[AudioManager] Audio inicializado correctamente." << std::endl;
    }
    engineInitialized = true;
}

void AudioManager::shutdown() {
    stopMusic();
    ma_engine_uninit(&engine);
    engineInitialized = false;
}

void AudioManager::playSound(const std::string& filePath) {
    if (ma_engine_play_sound(&engine, filePath.c_str(), NULL) != MA_SUCCESS) {
        std::cerr << "[AudioManager] Error al reproducir sonido: " << filePath << std::endl;
    }
}

void AudioManager::playMusic(const std::string& filePath, bool loop) {
    stopMusic();

    ma_result result = ma_sound_init_from_file(&engine, filePath.c_str(), MA_SOUND_FLAG_STREAM, NULL, NULL, &music);
    if (result != MA_SUCCESS) {
        std::cerr << "[AudioManager] Error al cargar música: " << filePath << std::endl;
        musicInitialized = false;
        return;
    }

    ma_sound_set_looping(&music, loop);
    ma_sound_start(&music);
    musicInitialized = true;
}


void AudioManager::stopMusic() {
    if (musicInitialized) {
        ma_sound_stop(&music);
        ma_sound_uninit(&music);
        musicInitialized = false;
    }
}