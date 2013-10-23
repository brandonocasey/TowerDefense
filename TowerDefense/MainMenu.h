#ifndef MAINMENU_H
#define MAINMENU_H

#include "BaseGameState.h"

class MainMenu : public BaseGameState
{
    public:
        void Init();
        void Cleanup();

        void Pause();
        void Resume();

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
        SDL_Surface* bg;
        GameLog logger;
};

#endif