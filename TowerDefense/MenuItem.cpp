#include "MenuItem.h"

MenuItem::MenuItem( int x, int y, int h, int w, std::string name )
{
    m_cCollision.x = x;
    m_cCollision.y = y;
    m_cCollision.w = w;
    m_cCollision.h = h;

    m_sName = name;

    SDL_Color color = { 255, 255, 255 };
    TTF_Font *font = nullptr;
    std::string font_file = "fonts/SourceSansPro-Regular.ttf";

    font = TTF_OpenFont(font_file.c_str(), 64);
    SDL_Surface *surf = TTF_RenderText_Blended(font, name.c_str(), color);
    //m_cCurrentTexture = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
}


std::string MenuItem::GetName()
{
    return m_sName;
}

SDL_Rect MenuItem::GetCollisionRect()
{
    return m_cCollision;
}