#ifndef RENDERHELPER_H
#define RENDERHELPER_H

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

        void ToggleFullscreen();

        bool FullscreenOn();
        bool FullscreenOff();

        void ResizeWindow();

    private:
        SDL_Renderer* m_cRenderer;
        SDL_Renderer* m_cWindow;
};

#endif
