#pragma once
#include "../Utils.h"
class RenderHelper
{
    public:
        void Init();
        void Cleanup();
        void RenderText();
        void RenderImage();
        SDL_Texture* LoadText():
        SDL_Texture* LoadImage();


        SDL_Rect GetTextDimensions();
        SDL_Rect GetTextureDimensions();
        SDL_Rect GetScreenDimensions();

        void GetWindowSize(int *width, int *height);

        void ToggleFullscreen();
        void ToggleFullScreen(bool fullscreen);

        void FullscreenOn();
        void FullscreenOff();

        void ResizeWindow(int width, int height);

    private:
        SDL_Renderer* m_cRenderer;
        SDL_Renderer* m_cWindow;
        int m_iWindowHeight;
        int m_iWindowWidth;
        bool m_bFullscreen;
};
