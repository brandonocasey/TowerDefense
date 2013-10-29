#pragma once
#include "../Utils.h"

class BaseGameState
{
    public:
        std::string m_sName;
        virtual void Init(GameEngine* game) = 0;
        virtual void Cleanup(GameEngine* game) = 0;

        virtual void Pause(GameEngine* game) = 0;
        virtual void Resume(GameEngine* game) = 0;

        virtual void HandleEvents(GameEngine* game) = 0;
        virtual void Update(GameEngine* game) = 0;
        virtual void Draw(GameEngine* game) = 0;

        void ChangeState(GameEngine* game, BaseGameState* state)
        {
            game->ChangeState(state);
        }

    protected:
        BaseGameState() { } // Constructor
        GameLog* logger;
};
