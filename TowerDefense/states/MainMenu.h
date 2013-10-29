#pragma once

#include "../Utils.h"
#include "../base_classes/BaseGameState.h"
#include "../classes/GameEngine.h"
#include "InGame.h"
#include "Settings.h"
#include "LoadGame.h"

class MenuItem;

class MainMenu : public BaseGameState
{
    public:
        void QuitCallback(GameEngine* game);
        void NewGameCallback(GameEngine* game);
        void LoadGameCallback(GameEngine* game);
        void SettingsCallback(GameEngine* game);

        void Init(GameEngine* game);
        void Cleanup(GameEngine* game);

        void Pause(GameEngine* game);
        void Resume(GameEngine* game);

        void HandleEvents(GameEngine* game);
        void Update(GameEngine* game);
        void Draw(GameEngine* game);

        static MainMenu* Instance()
        {
            return &m_MainMenu;
        }

    protected:
        MainMenu() { }

    private:
        static MainMenu m_MainMenu;
        std::vector<MenuItem*> m_vMenuItems;
        GameLog *logger;
};
