#ifndef MENUITEM_H
#define MENUITEM_H

class BaseGameState; // So that we can fill out vector

#include "utils.h"

class MenuItem
{
    public:
        MenuItem( int x, int y, int h, int w, std::string name );
        void Action();
        void MouseOver();
        std::string GetName();
        SDL_Rect GetCollisionRect();
    private:
        SDL_Texture* m_cCurrentTexture;
        std::string m_sName;
        SDL_Rect m_cCollision;
};

#endif
