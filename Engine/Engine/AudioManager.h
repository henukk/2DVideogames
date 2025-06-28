#ifndef _AUDIO_MANAGER_INCLUDE
#define _AUDIO_MANAGER_INCLUDE

#include <string>
#include "miniaudio.h"

class AudioManager {
public:
    static AudioManager& instance();

    void init();
    void shutdown();

    void playSound(const std::string& filePath);
    void playMusic(const std::string& filePath, bool loop = true);
    void stopMusic();

private:
    AudioManager();
    ~AudioManager();

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

private:
    ma_engine engine;
    ma_sound music;
    bool musicInitialized;
    bool engineInitialized;
};

#endif // _AUDIO_MANAGER_INCLUDE
