#ifndef MENUITEM_H
#define MENUITEM_H

#include "utils.h"
#include "GameEngine.h"

class MainMenu;

class MenuItem
{
    public:
        // in our constructor we store the function that we need to run when we are selected
        MenuItem( std::string text, boost::function<void(GameEngine* game)> action_function );

        // The menu passes us a callback function
        // When we get selected and clicked on we call this
        void Callback(GameEngine* game);

        // Tell the menu item what state to draw
        void Update(GameEngine* game);

        // Draw the menu item where the menu tells us
        void Draw(GameEngine* game, int x, int y);

        // return the required height of our text
        int GetHeight();

        // return the required width of out text
        int GetWidth();

        // Cleanup our texture
        void Cleanup();


        // Check if we are currenly being selected by the mouse
        bool CheckMouse();


    private:
        // Our Callback function from the menu
        boost::function<void(GameEngine* game)> m_fMenuCallback;
        // Whether or not we are selected
        bool m_bSelected;

        // Useful function to help us draw
        void SetCurrentSurface(SDL_Color font_color );
        void SetCurrentSurface();

        SDL_Surface* m_cCurrentSurface;
        SDL_Rect m_cPosition;
        // The main event, our menu text
        std::string m_sText;
        TTF_Font* m_cFont;
        GameLog logger;
};

#endif
