#ifndef LOADGAME_H
#define LOADGAME_H

#include "utils.h"
#include "BaseGameState.h"
#include "MenuItem.h"

class LoadGame : public BaseGameState
{
    public:
        void Init();
        void Cleanup();

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
        GameLog logger;
};

#endif