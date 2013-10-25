#ifndef AUDIOHELPER_H
#define AUDIOHELPER_H

class AudioHelper
{
    public:
        void Init();
        void Cleanup(); // Mix_CloseAudio();

        Mix_Music* LoadMusic( std::string location );
        Mix_Chunk* LoadSound( std::string location );

        // Which channel to play on, -1 is whatever is available, chunk, how many times to loop
        void PlaySound(Mix_Chunk* sound); // Mix_PlayChannel( -1, scratch, 0 ) == -1
        void PlayMusic(Mix_Chunk* music);

        void PlaySound(std::string sound_location);
        void PlayMusic(std::string music_location);

        void PauseMusic();
        void ToggleMusic();
        void ToggleSound();
        void ToggleBoth();

        void SetMusicVolume(int level);
        void SetSoundsVolume(int level);
        void SetAllVolume(int level);

        int GetAllVolume();
        int GetMusicVolume();
        int GetSoundVolume();


        void HaltMusic();
    private:
        GameLog logger;
        int m_iSoundVolume;
        int m_iAllVolume;
        int m_iMusicVolume;
        int m_iPreviousSoundVolume;
        int m_iPreviousAllVolume;
        int m_iPreviousMusicVolume;
};

#endif
