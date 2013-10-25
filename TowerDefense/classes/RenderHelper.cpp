#include "RenderHelper.h"

void RenderHelper::Init()
{
    m_cWindow = nullptr;
    m_cWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if( m_cWindow == nullptr )
    {
        logger.LogError( std::string("SDL_CreateWindow: ") + SDL_GetError() );
        return 2;
    }
    else
    {
        logger.Log("SDL_CreateWindow was successful");
    }

    m_cRenderer = nullptr;
    m_cRenderer = SDL_CreateRenderer(m_cWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    if( m_cRenderer == nullptr )
    {
        logger.LogError( std::string("SDL_CreateRenderer: ") + SDL_GetError() );
        return 3;
    }
    else
    {
        logger.Log("SDL_CreateRenderer was successful");
    }

    int img_flags = IMG_INIT_JPG|IMG_INIT_PNG;
    if ((IMG_Init(img_flags) != img_flags))
    {
        logger.LogError("IMG_Init failed to init jpeg with error "  + std::string(SDL_GetError()) );
        return 4;
    }
    else
    {
        logger.Log("IMG_Init was successful!");
    }

    if (TTF_Init() == -1)
    {
        logger.LogError("TTF_Init Failed with error: "  + std::string(TTF_GetError()) );
        return 5;
    }
    else
    {
        logger.Log("TTF_Init was successful!");
    }
}

void RenderHelper::Cleanup()
{
    SDL_DestroyRenderer(m_cRenderer);
    SDL_DestroyWindow(m_cWindow);

    IMG_Quit();
    TTF_Quit();
}

/**
 * Toggle fullscreen using the internal GameEngine Variable
 */
void RenderHelper::ToggleFullScreen()
{
    logger.Log("Toggle Fullscreen");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(m_cRenderer, m_iScreenWidth, m_iScreenHeight);
    if( ! m_bFullscreen )
    {
        if( FullscreenOn() )
        {
            m_bFullscreen = true;
            logger.LogError("Fullscreen successfully initialized");
        }
        else
        {
            logger.LogError("Turning Fullscreen On failed with error " + std::string(SDL_GetError()));
        }
    }
    else
    {
        if( FullscreenOff() )
        {
            m_bFullscreen = false;
            logger.LogError("Fullscreen successfully turned off");
        }
        else
        {
            logger.LogError("Turning Fullscreen off failed with error " +  std::string(SDL_GetError()));
        }
    }
}

bool RenderHelper::FullscreenOn()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_cRenderer, m_iScreenWidth, m_iScreenHeight);
    SDL_SetWindowFullscreen(m_cWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    m_bFullscreen = true;
}

bool RenderHelper::FullscreenOff()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_cRenderer, m_iScreenWidth, m_iScreenHeight);
    SDL_SetWindowFullscreen(m_cWindow, SDL_FALSE);
    m_bFullscreen = false;
}
