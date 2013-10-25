#ifndef BASEGAMESTATE_H
#define BASEGAMESTATE_H

#include "GameEngine.h"
#include "utils.h"

class BaseGameState
{
    public:
        std::string m_sName;
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents(GameEngine* game) = 0;
        virtual void Update(GameEngine* game) = 0;
        virtual void Draw(GameEngine* game) = 0;

        void ChangeState(GameEngine* game, BaseGameState* state)
        {
            game->ChangeState(state);
        }

    protected:
        BaseGameState() { } // Constructor
        GameLog logger;
};

#endif