#include "MenuItem.h"

MenuItem::MenuItem( int x, int y, int h, int w, std::string name )
{
    m_bMouseOnTop = false;
    m_cCollision.x = x;
    m_cCollision.y = y;
    m_cCollision.w = w;
    m_cCollision.h = h;

    m_sName = name;

    SDL_Color color = { 255, 255, 255 };
    TTF_Font *font = nullptr;
    std::string font_file = MENU_FONT;

    font = TTF_OpenFont(font_file.c_str(), 24);

    m_sName = name;
    m_cCurrentSurface = TTF_RenderText_Blended(font, name.c_str(), color);

    TTF_CloseFont(font);
}

void MenuItem::MouseOver()
{
    m_bMouseOnTop = true;
    if(m_cCurrentSurface != nullptr)
    {
        SDL_FreeSurface(m_cCurrentSurface);
        m_cCurrentSurface = nullptr;
    }
    SDL_Color color = { 255, 0, 0 };
    TTF_Font *font = nullptr;
    std::string font_file = MENU_FONT;

    font = TTF_OpenFont(font_file.c_str(), 24);
    m_cCurrentSurface = TTF_RenderText_Blended(font, m_sName.c_str(), color);

    TTF_CloseFont(font);
}

void MenuItem::MouseOut()
{
    m_bMouseOnTop = false;
    if(m_cCurrentSurface != nullptr)
    {
        SDL_FreeSurface(m_cCurrentSurface);
        m_cCurrentSurface = nullptr;
    }
    SDL_Color color = { 255, 255, 255 };
    TTF_Font *font = nullptr;
    std::string font_file = MENU_FONT;

    font = TTF_OpenFont(font_file.c_str(), 24);
    m_cCurrentSurface = TTF_RenderText_Blended(font, m_sName.c_str(), color);

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