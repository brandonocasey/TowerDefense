#include "MenuItem.h"
#include "MainMenu.h"

//MenuItem::MenuItem( int x, int y, int h, int w, std::string name, void (MainMenu::*action_function)(GameEngine* game) )
MenuItem::MenuItem( int x, int y, int h, int w, std::string name )
{
    m_bSelected = false;
    m_cCurrentSurface = nullptr;

    m_cCollision.x = x;
    m_cCollision.y = y;
    m_cCollision.w = w;
    m_cCollision.h = h;

    m_sName = name;
    SetCurrentSurface();

    // Action function to run
    //m_fAction = action_function;
}

void MenuItem::Action(GameEngine* game)
{
    // Stored action function to run when clicked
   //&m_fAction(game);
}
void MenuItem::Selected()
{
    m_bSelected = true;
    SDL_Color color = { 255, 0, 0 };
    SetCurrentSurface(color);
}

bool MenuItem::IsSelected()
{
    return m_bSelected;
}

void MenuItem::UnSelected()
{
    m_bSelected = false;
    SetCurrentSurface();
}

void MenuItem::SetCurrentSurface()
{
    SDL_Color font_color = {255, 255, 255};
    SetCurrentSurface(font_color);
}

void MenuItem::SetCurrentSurface(SDL_Color font_color )
{
    if(m_cCurrentSurface != nullptr)
    {
        SDL_FreeSurface(m_cCurrentSurface);
        m_cCurrentSurface = nullptr;
    }
    TTF_Font *font = nullptr;
    std::string font_file = MENU_FONT;

    font = TTF_OpenFont(font_file.c_str(), 16);
    m_cCurrentSurface = TTF_RenderText_Blended(font, m_sName.c_str(), font_color);

    TTF_CloseFont(font);
}

void MenuItem::Cleanup()
{
    SDL_FreeSurface(m_cCurrentSurface);
}
std::string MenuItem::GetName()
{
    return m_sName;
}

SDL_Rect MenuItem::GetCollisionRect()
{
    return m_cCollision;
}

bool MenuItem::CheckMouse(int mouse_x, int mouse_y)
{
    
    if( ( mouse_x > m_cCollision.x ) && ( mouse_x < m_cCollision.x + m_cCollision.w ) && ( mouse_y > m_cCollision.y ) && ( mouse_y < m_cCollision.y + m_cCollision.h ) )
    {
        return true;
    }

    return false;
}
