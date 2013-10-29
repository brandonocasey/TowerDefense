#pragma once
#include "../Utils.h"
class RenderHelper
{
    public:
        bool Init(const char* title, int width, int height, bool fullscreen);
        void Cleanup();
        void RenderText();
        void RenderImage();
        TTF_Font* LoadFont(std::string font_location, int font_size);
        SDL_Texture* LoadText(std::string font_location, int font_size, std::string text, SDL_Color font_color);
        SDL_Texture* LoadImage(std::string image_location);
        void GetFontSize(TTF_Font* font, std::string text, int *width, int *height);
        void GetTextureSize(SDL_Texture* texture, int *width, int *height);

        void RenderTexture(SDL_Texture* text_texture, SDL_Rect destination, SDL_Rect source);

        void GetWindowSize(int *width, int *height);

        void ToggleFullscreen();
        void ToggleFullscreen(bool fullscreen);

        void FullscreenOn();
        void FullscreenOff();

        void ClearScrean();

        void ResizeWindow(int width, int height);

        void RenderHelper::RenderText(std::string font_location, int font_size, std::string text, SDL_Color color, SDL_Rect destination, SDL_Rect source);
        void RenderHelper::RenderImage(std::string image_location, SDL_Rect destination, SDL_Rect source);

    private:
        GameLog* logger;
        std::string m_sName;
        SDL_Renderer* m_cRenderer;
        SDL_Window* m_cWindow;
        int m_iWindowHeight;
        int m_iWindowWidth;
        bool m_bFullscreen;
        int m_iPreviousWindowWidth;
        int m_iPreviousWindowHeight;
};
