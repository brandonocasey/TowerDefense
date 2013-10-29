#pragma once

#include "../Utils.h"
#include "../base_classes/BaseGameState.h"
#include "../classes/MenuItem.h"
#include "../classes/GameEngine.h"

class Settings : public BaseGameState
{
    public:
        void Init(GameEngine* game);
        void Cleanup(GameEngine* game);

        void Pause(GameEngine* game);
        void Resume(GameEngine* game);

        void HandleEvents(GameEngine* game);
        void Update(GameEngine* game);
        void Draw(GameEngine* game);

        void MasterVolumeCallback(GameEngine* game);
        void SoundVolumeCallback(GameEngine* game);
        void MusicVolumeCallback(GameEngine* game);
        void ToggleFullscreenCallback(GameEngine* game);
        void BrightnessCallback(GameEngine* game);
        void ResizeWindowCallback(GameEngine* game);
        void BackCallback(GameEngine* game);
        void ClearSaveDataCallback(GameEngine* game);

        static Settings* Instance()
        {
            return &m_Settings;
        }

    protected:
        Settings() { }

    private:
        static Settings m_Settings;
        std::vector<MenuItem*> m_vMenuItems;
        GameLog *logger;
};