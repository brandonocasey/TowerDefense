#ifndef NEWGAME_H
#define NEWGAME_H

#include "utils.h"
#include "BaseGameState.h"

// How do I pass a map here?
class NewGame : public BaseGameState
{
    public:
        void Init();
        void Cleanup();

        void Pause(GameEngine* game);
        void Resume(GameEngine* game);

        void HandleEvents(GameEngine* game);
        void Update(GameEngine* game);
        void Draw(GameEngine* game);

        void LoadMap(std::string map_location);
        static NewGame* Instance()
        {
            return &m_NewGame;
        }

    protected:
        NewGame() { }

    private:
        static NewGame m_NewGame;
        GameLog logger;
};

#endif