#include "MenuItem.h"
#include "../states/MainMenu.h"

MenuItem::MenuItem( std::string name, boost::function<void(GameEngine* game)> action_function )
{
    logger.GetLogger(name);
    m_bSelected = false;

    m_sText = name;

    // Action function to run
    m_fMenuCallback = action_function;

    m_cFont = nullptr;
    std::string font_file = MENU_FONT;


    m_cFont = TTF_OpenFont(font_file.c_str(), 24);
    if( m_cFont == nullptr )
    {
        logger.LogError("There was an error loading the font");
    }

    m_cCurrentSurface = nullptr;

    SetCurrentSurface();
}

void MenuItem::Callback(GameEngine* game)
{
    // Stored action function to run when clicked
    if( this->CheckMouse() )
    {
        logger.Log("User Clicked Me");
        m_fMenuCallback(game);
    }
}


void MenuItem::SetCurrentSurface()
{
    SDL_Color font_color = {255, 255, 255};
    SetCurrentSurface(font_color);
}

void MenuItem::SetCurrentSurface(SDL_Color font_color)
{
    if(m_cCurrentSurface != nullptr)
    {
        SDL_FreeSurface(m_cCurrentSurface);
        m_cCurrentSurface = nullptr;
    }

    m_cCurrentSurface = TTF_RenderText_Solid(m_cFont, m_sText.c_str(), font_color);
    if( m_cCurrentSurface == nullptr )
    {
        logger.LogError("There was an error loading the surface");
    }
}

void MenuItem::Cleanup()
{
    TTF_CloseFont(m_cFont);
    m_cFont = nullptr;
    SDL_FreeSurface(m_cCurrentSurface);
    m_cCurrentSurface = nullptr;
}

void MenuItem::Draw(GameEngine* game, int x, int y)
{
    m_cPosition.x = x;
    m_cPosition.y = y;
    m_cPosition.h = GetHeight();
    m_cPosition.w = GetWidth();


    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->m_cRenderer,m_cCurrentSurface);
    SDL_RenderCopy(game->m_cRenderer, texture, NULL, &m_cPosition );

    SDL_DestroyTexture(texture);

}

void MenuItem::Update(GameEngine* game)
{
    if( CheckMouse() )
    {
        SDL_Color color = {255, 0, 0};
        SetCurrentSurface(color);
    }
    else
    {
        SetCurrentSurface();
    }
}

bool MenuItem::CheckMouse()
{
    int mouse_x = 0;
    int mouse_y = 0;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    if( ( mouse_x > m_cPosition.x ) && ( mouse_x < m_cPosition.x + m_cPosition.w ) && ( mouse_y > m_cPosition.y ) && ( mouse_y < m_cPosition.y + m_cPosition.h ) )
    {
        return true;
    }

    return false;
}

int MenuItem::GetHeight()
{
    int h = 0;

    TTF_SizeText(m_cFont, m_sText.c_str(), nullptr, &h);
    return h;
}

int MenuItem::GetWidth()
{
    int w = 0;

    TTF_SizeText(m_cFont, m_sText.c_str(), &w, nullptr);
    return w;
}