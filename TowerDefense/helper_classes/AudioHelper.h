#pragma once
#include "../Utils.h"

class AudioHelper
{
    public:
        void Init(int channels = 2, int chunksize = 4096, int frequency = 22050);
        void Cleanup();

        Mix_Music* LoadMusic( std::string location );
        Mix_Chunk* LoadSound( std::string location );

        void PlaySound(Mix_Chunk* sound);
        void PlayMusic(Mix_Chunk* music);

        void PlaySound(std::string sound_location);
        void PlayMusic(std::string music_location);
        void AudioHelper::PlayMusic( Mix_Music* music );

        void PauseMusic();
        void ToggleMusic();
        void ToggleSound();
        void ToggleAll();

        void SetMusicVolume(int level);
        void SetSoundVolume(int level);
        void SetAllVolume(int level);
        void SetChannels(int number_of_channels);

        int GetAllVolume();
        int GetMusicVolume();
        int GetSoundVolume();


        void HaltMusic();
    private:
        GameLog *logger;
        std::string m_sName;
        int m_iSoundVolume;
        int m_iAllVolume;
        int m_iMusicVolume;
        int m_iPreviousSoundVolume;
        int m_iPreviousAllVolume;
        int m_iPreviousMusicVolume;
};
