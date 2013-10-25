#ifndef MENUITEM_H
#define MENUITEM_H

#include "utils.h"
#include "GameEngine.h"

class MainMenu;

class MenuItem
{
    public:
        // in our constructor we store the function that we need to run when we are selected
       // MenuItem( int x, int y, int h, int w, std::string name,  void (MainMenu::*action_function)(GameEngine* game) );
        MenuItem( int x, int y, int h, int w, std::string name );

        void SetAction();
        void Action(GameEngine* game);
        void Selected();
        void UnSelected();
        bool IsSelected();
        std::string GetName();
        SDL_Rect GetCollisionRect();
        void Cleanup();
        SDL_Surface* m_cCurrentSurface;
        bool CheckMouse(int mouse_x, int mouse_y);
    private:

        void (*MainMenu::*m_fAction)(GameEngine* game);
        bool m_bSelected;
        void SetCurrentSurface(SDL_Color font_color );
        void SetCurrentSurface();
        std::string m_sName;
        SDL_Rect m_cCollision;
};

#endif
