#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "utils.h"
class BaseGameState; // Forward decleration so that we can use BaseGameState in two places

class GameEngine
{
    public:
        int m_iScreenHeight;
        int m_iScreenWidth;
        // Creating and destroying the state machine
        int Init(const char* title, int width, int height, bool fullscreen);
        void Cleanup();

        // Things that will need to be controlled in the options menu
        void ToggleFullScreen();
        void ToggleFullScreen(bool fullscreen);
        void ResizeWindow(int width, int height);
        void ChangeVolumeLevel(int level);
        void ChangeBrightness(int level);
        void ClearSaveData();

        //For use inbetween screens
        void ClearScreen();

        // Transit between states
        void ChangeState(BaseGameState* state);
        void PushState(BaseGameState* state);
        void PopState();

        // The three important actions within a game loop
        // (these will be handled by the top state in the stack)
        void HandleEvents();
        void Update();
        void Draw();

        // Tells the main loop whether to keep looping or not.
        bool Running();

        // Run the main loop with only one function call
        void Run();

        // sets m_bRunning to false which makes running return false
        void Quit();

        SDL_Renderer* m_cRenderer;

    private:
        std::vector<BaseGameState*> states;
        GameLog logger;
        SDL_Window* m_cWindow;
        bool m_bRunning;
        bool m_bFullscreen;
};

#endif
