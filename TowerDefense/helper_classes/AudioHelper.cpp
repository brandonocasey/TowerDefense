#include "AudioHelper.h"

void AudioHelper::Init(int channels = 2, int chunksize = 4096, int frequency = 22050)
{
    m_sName = "AudioHelper";
    logger->GetLogger(m_sName);
    m_iSoundVolume = MIX_MAX_VOLUME;
    m_iAllVolume = MIX_MAX_VOLUME;
    if( Mix_OpenAudio( frequency, MIX_DEFAULT_FORMAT, channels, chunksize ) == -1 )
    {
        logger->LogSdlError( "Mix_OpenAudio" );
    }
    else
    {
        logger->Log("AudioHelper Successfully initialized");
    }
}

void AudioHelper::Cleanup()
{
    Mix_CloseAudio();
}

void AudioHelper::HaltMusic()
{
    Mix_HaltMusic();
}

void AudioHelper::SetChannels(int number_of_channels)
{
    Mix_AllocateChannels(number_of_channels);
}

void AudioHelper::SetMusicVolume(int level)
{
    // MIX_MAX_VOLUME == 128
    if( level > MIX_MAX_VOLUME )
    {
        logger->Log("Setting music volume level to max volume " + std::to_string(MIX_MAX_VOLUME) + " because level of " + std::to_string(level) + " was over Max Volume");
        level = MIX_MAX_VOLUME;
    }

    int min_volume = 0;
    if( level < min_volume )
    {
        logger->Log("Setting music volume level to min_volume " + std::to_string(min_volume) + " because level of " + std::to_string(level) + " was under minimum Volume");
        level = MIX_MAX_VOLUME;
    }

    logger->Log("Setting music volume level to " + std::to_string(level));
    Mix_VolumeMusic(level);
    m_iMusicVolume = level;

}

int AudioHelper::GetMusicVolume()
{
    int level = Mix_VolumeMusic(-1);
    return level;
}


void AudioHelper::SetSoundVolume(int level)
{
    // MIX_MAX_VOLUME == 128
    if( level > MIX_MAX_VOLUME )
    {
        logger->Log("Setting sound volume level to max volume " + std::to_string(MIX_MAX_VOLUME) + " because level of " + std::to_string(level) + " was over Max Volume");
        level = MIX_MAX_VOLUME;
    }

    int min_volume = 0;
    if( level < min_volume )
    {
        logger->Log("Setting sound volume level to min_volume " + std::to_string(min_volume) + " because level of " + std::to_string(level) + " was under minimum Volume");
        level = MIX_MAX_VOLUME;
    }

    logger->Log("Setting sound volume level to " + std::to_string(level));
    m_iSoundVolume = level;
}

int AudioHelper::GetSoundVolume()
{
    return m_iSoundVolume;
}


void AudioHelper::SetAllVolume(int level)
{
    if( level > MIX_MAX_VOLUME )
    {
        logger->Log("Setting sound volume level to max volume " + std::to_string(MIX_MAX_VOLUME) + " because level of " + std::to_string(level) + " was over Max Volume");
        level = MIX_MAX_VOLUME;
    }

    int min_volume = 0;
    if( level < min_volume )
    {
        logger->Log("Setting sound volume level to min_volume " + std::to_string(min_volume) + " because level of " + std::to_string(level) + " was under minimum Volume");
        level = MIX_MAX_VOLUME;
    }

    Mix_Volume(-1, level);
    m_iAllVolume = level;
}

int AudioHelper::GetAllVolume()
{
    return m_iAllVolume;
}

Mix_Music* AudioHelper::LoadMusic( std::string location )
{
    Mix_Music* music = nullptr;
    music = Mix_LoadMUS( location.c_str() );

    if( music == nullptr )
    {
        logger->LogSdlError("Mix_LoadMUS");
    }
    else
    {
        logger->Log("Successfully loaded sound");
    }

    return music;
}

Mix_Chunk* AudioHelper::LoadSound( std::string location )
{
    Mix_Chunk* sound = nullptr;
    sound = Mix_LoadWAV( location.c_str() );

    if( sound == nullptr )
    {
        logger->LogError("Mix_LoadWAV");
    }
    else
    {
        logger->Log("Successfully loaded sound at " + location);
    }

    return sound;
}

void AudioHelper::PlayMusic( Mix_Music* music )
{
    // 0 is loop until we stop it
    Mix_PlayMusic(music, 0);
}

void AudioHelper::PlayMusic( std::string music_location )
{
    PlayMusic( LoadMusic(music_location) );
}

void AudioHelper::PlaySound( Mix_Chunk* sound )
{
    // -1 is next available channel
    // 0 is how many times to loop
    Mix_VolumeChunk(sound, m_iSoundVolume);
    Mix_PlayChannel(-1, sound, 0);
}

void AudioHelper::PlaySound( std::string sound_location )
{
    PlaySound( LoadSound(sound_location) );
}

void AudioHelper::PauseMusic()
{
    //If there is no music playing
    if( Mix_PlayingMusic() == 0 )
    {
        logger->LogError("There is currently no music playing, but pause music called!");
    }
    //If music is being played
    else
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
    }
}

void AudioHelper::ToggleSound()
{
    m_iPreviousSoundVolume = m_iSoundVolume;
    if( m_iSoundVolume > 0 )
    {
        SetSoundVolume(0);
    }
    else
    {
        SetSoundVolume(m_iPreviousSoundVolume);
    }
}

void AudioHelper::ToggleAll()
{
    m_iPreviousAllVolume = m_iAllVolume;
    if( m_iAllVolume > 0 )
    {
        SetAllVolume(0);
    }
    else
    {
        SetAllVolume(m_iPreviousAllVolume);
    }
}

void AudioHelper::ToggleMusic()
{
    m_iPreviousMusicVolume = m_iMusicVolume;
    if( m_iMusicVolume > 0 )
    {
        SetSoundVolume(0);
    }
    else
    {
        SetSoundVolume(m_iPreviousMusicVolume);
    }
}
