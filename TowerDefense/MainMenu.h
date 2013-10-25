#ifndef MAINMENU_H
#define MAINMENU_H

#include "utils.h"
#include "BaseGameState.h"
class MenuItem;

class MainMenu : public BaseGameState
{
    public:
        void Quit(GameEngine* game);
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
        std::vector<MenuItem*> m_vMenuItems;
        GameLog logger;
};

#endif