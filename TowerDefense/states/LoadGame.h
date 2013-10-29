#pragma once

#include "../Utils.h"
#include "../base_classes/BaseGameState.h"
#include "../classes/MenuItem.h"

class LoadGame : public BaseGameState
{
    public:
        void Init(GameEngine* game);
        void Cleanup(GameEngine* game);

        void Pause(GameEngine* game);
        void Resume(GameEngine* game);

        void HandleEvents(GameEngine* game);
        void Update(GameEngine* game);
        void Draw(GameEngine* game);

        static LoadGame* Instance()
        {
            return &m_LoadGame;
        }

    protected:
        LoadGame() { }

    private:
        static LoadGame m_LoadGame;
        std::vector<MenuItem*> m_vMenuItems;
        GameLog *logger;
};