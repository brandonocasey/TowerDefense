#include "RenderHelper.h"

/**
 * This function initializes something that will help us render fonts and images
 * @param title      the title of the window
 * @param width      the width of the window
 * @param height     the height of the window
 * @param fullscreen whether to start out in fullsceen or not
 */
bool RenderHelper::Init(const char* title, int width, int height, bool fullscreen)
{
    m_sName = "RenderHelper";
    logger = logger->GetLogger(m_sName);
    // Initialize variables
    m_cRenderer = nullptr;
    m_cWindow = nullptr;

    m_iWindowHeight = height;
    m_iWindowWidth = width;

    m_bFullscreen = false;

    m_cWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if( m_cWindow == nullptr )
    {
        logger->LogSdlError("SDL_CreateWindow");
        return false;
    }
    else
    {
        logger->Log("SDL_CreateWindow was successful");
    }

    m_cRenderer = nullptr;
    m_cRenderer = SDL_CreateRenderer(m_cWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    if( m_cRenderer == nullptr )
    {
        logger->LogSdlError("SDL_CreateRenderer");
        return false;
    }
    else
    {
        logger->Log("SDL_CreateRenderer was successful");
    }

    int img_flags = IMG_INIT_JPG|IMG_INIT_PNG;
    if ((IMG_Init(img_flags) != img_flags))
    {
        logger->LogSdlError("IMG_Init");
        return false;
    }
    else
    {
        logger->Log("IMG_Init was successful!");
    }

    if (TTF_Init() == -1)
    {
        logger->LogSdlError("TTF_Init");
        return false;
    }
    else
    {
        logger->Log("TTF_Init was successful!");
    }

    ToggleFullscreen(fullscreen);

    return true;
}

void RenderHelper::Cleanup()
{
    SDL_DestroyRenderer(m_cRenderer);
    SDL_DestroyWindow(m_cWindow);

    IMG_Quit();
    TTF_Quit();
}

/**
 * Toggle fullscreen using the internal Variable
 */
void RenderHelper::ToggleFullscreen()
{
    logger->Log("Toggle Fullscreen internal variable");
    if( ! m_bFullscreen )
    {
        FullscreenOn();
    }
    else
    {
        FullscreenOff();
    }
}

/**
 * Toggle fullscreen using the variable that is passed to us
 * @param fullscreen if true we want fullscreen on, otherwise it is off
 */
void RenderHelper::ToggleFullscreen(bool fullscreen)
{
    logger->Log("Toggle Fullscreen");
    if( fullscreen )
    {
        FullscreenOn();
    }
    else
    {
        FullscreenOff();
    }
}

/**
 * Turn Fullscreen on and save previous screen size.
 */
void RenderHelper::FullscreenOn()
{
    GetWindowSize(&m_iPreviousWindowWidth, &m_iPreviousWindowHeight);
    // We store this so that if they toggle back out of fullscreen
    // We can resize the window from the crazy resolution that the window
    // will end up as
    if( SDL_SetWindowFullscreen(m_cWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) == 0 )
    {
        logger->Log("Fullscreen successfully initialized");
    }
    else
    {
        logger->LogSdlError("SDL_SetWindowFullscreen on");
    }
    m_bFullscreen = true;
}

/**
 * Turn fullscreen off and restore previous screen size if it exists
 */
void RenderHelper::FullscreenOff()
{
    m_bFullscreen = false;
    if( SDL_SetWindowFullscreen(m_cWindow, SDL_FALSE) == 0 )
    {
        logger->Log("Fullscreen successfully turned off");
    }
    else
    {
        logger->LogSdlError("SDL_SetWindowFullscreen off");
    }

    // Window is really big after fullscreen turns of if we don't do this.
    if( m_iPreviousWindowWidth && m_iPreviousWindowWidth )
    {
        ResizeWindow(m_iPreviousWindowWidth, m_iPreviousWindowHeight);
    }
}

/**
 * Resize the game window, for use with the setting menu. Also saves previous window size
 * For things that need to revert the window size
 * @param width  width of the screen
 * @param height height of the screen
 */
void RenderHelper::ResizeWindow(int width, int height)
{
    logger->Log("Resizing window to h = " + std::to_string(height) + " w = " + std::to_string(width));
    SDL_SetWindowSize(m_cWindow, width, height);
    m_iWindowWidth = width;
    m_iWindowHeight = height;
}


/**
 * Clear the Screen to black
 */
void RenderHelper::ClearScrean()
{
    SDL_SetRenderDrawColor(m_cRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_cRenderer);
    SDL_RenderPresent(m_cRenderer);
}

/**
 * Get the size of the current window
 * @param width  a pointer to be filled with the width of the current window
 * @param height a pointer to be filled with the height of the current window
 */
void RenderHelper::GetWindowSize( int *width, int *height )
{
    SDL_GetWindowSize( m_cWindow, width, height);

    logger->Log("Current window is h = " + std::to_string(*height) + " w = " + std::to_string(*width));
}


/**
 * Load a texture filled with text using SDL_ttf
 * @param  font_location the location of the font file to be used
 * @param  font_size     the size of the font in pixels
 * @param  text          the text to be printed with the font
 * @param  font_color    The Color to make the font
 * @return               The texture object containing the font
 */
SDL_Texture* RenderHelper::LoadText(std::string font_location, int font_size, std::string text, SDL_Color font_color)
{
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture *texture = nullptr;

    font = LoadFont(font_location, font_size);
    surface = TTF_RenderText_Solid(font, text.c_str(), font_color);
    if( surface = nullptr )
    {
        logger->LogSdlError("TTF_RenderText_Solid/LoadText");
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(m_cRenderer,surface);
        if( texture = nullptr )
        {
            logger->LogSdlError("SDL_CreateTextureFromSurface/LoadText");
        }
    }

    TTF_CloseFont(font);
    font = nullptr;
    SDL_FreeSurface(surface);
    surface = nullptr;


    return texture;
}

/**
 * Load an image file into a texture
 * @param  image_location The location of the image to load into a texture
 * @return                Return a texture object containing the image
 */
SDL_Texture* RenderHelper::LoadImage(std::string image_location)
{
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture( m_cRenderer, image_location.c_str() );
    if( texture = nullptr )
    {
        logger->LogSdlError("IMG_LoadTexture/LoadImage with asset " + image_location );
    }

    return texture;
}

/**
 * Load a font file into an SDL_font object
 * @param  font_location the location of the font
 * @param  font_size     the size of the fonts text
 * @return font          an SDL object containing the font
 */
TTF_Font* RenderHelper::LoadFont(std::string font_location, int font_size)
{
    TTF_Font* font = nullptr;
    font = TTF_OpenFont(font_location.c_str(), font_size);
    if( font == nullptr )
    {
        logger->LogSdlError("TTF_OpenFont/LoadText");
    }

    return font;
}

/**
 * Get the size of a texture
 * @param texture the texture to find the width an height of
 * @param width   a pointer to be filled with the width of a texture
 * @param height  a pointer to be filed with the height of a texture
 */
void RenderHelper::GetTextureSize(SDL_Texture* texture, int *width, int *height)
{
    SDL_QueryTexture(texture, NULL, NULL, width, height);
}

/**
 * This function gets the height and width of a specific font with text
 * @param  font   An SDL font object
 * @param  text   the text that will probably be going into that object
 * @param  width  a pointer to be filled with that fonts width
 * @param  height a pointer to be filled with that fonts height
 */
void RenderHelper::GetFontSize(TTF_Font* font, std::string text, int *width, int *height)
{
    TTF_SizeText(font, text.c_str(), width, height);
}

/**
 * Render a texture that has already been loaded
 * @param text_texture the texture to render
 * @param destination  the destination of that texture
 */
void RenderHelper::RenderTexture(SDL_Texture* texture, SDL_Rect destination, SDL_Rect source)
{
    if( !destination.w )
    {
        GetTextureSize(texture, &destination.w, NULL);
    }

    if( !destination.h )
    {
        GetTextureSize(texture, NULL, &destination.h);
    }


    SDL_RenderCopy(m_cRenderer, texture, &source, &destination);
    SDL_RenderPresent(m_cRenderer);
}

/**
 * Render text without doing a load first
 * @param font_location location of the font file to load
 * @param font_size     size of the font
 * @param text          text for the font
 * @param color         color for the font
 * @param destination   destination rect for the font
 * @param source        defaults to null, if you want part of a font add this
 */
void RenderHelper::RenderText(std::string font_location, int font_size, std::string text, SDL_Color color, SDL_Rect destination, SDL_Rect source)
{
    SDL_Texture* text_texture = LoadText(font_location, font_size, text, color);
    RenderTexture(text_texture, destination, source);

    SDL_DestroyTexture(text_texture);
}

void RenderHelper::RenderImage(std::string image_location, SDL_Rect destination, SDL_Rect source)
{
    SDL_Texture* image_texture = LoadImage(image_location);
    RenderTexture(image_texture, destination, source);
    SDL_DestroyTexture(image_texture);
}
