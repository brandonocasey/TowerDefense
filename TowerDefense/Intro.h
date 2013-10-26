#ifndef INTRO_H
#define INTRO_H

// This will be the state directly after the intro
// Change it here and a few other places.

#include "MainMenu.h"

class Intro : public BaseGameState
{
    public:
        void Init();
        void Cleanup();

        void Pause(GameEngine* game);
        void Resume(GameEngine* game);

        void HandleEvents(GameEngine* game);
        void Update(GameEngine* game);
        void Draw(GameEngine* game);

        void NextState(GameEngine* game);
        static Intro* Instance()
        {
            return &m_Intro;
        }

    protected:
        Intro() {}

    private:

        void StartTimer();
        bool TimerOver();
        static Intro m_Intro;
        std::vector<std::string> m_vBackgrounds;
        SDL_Texture* m_cCurrentTexture;
        int m_iCountdownStart;
        int m_iCountdownTotalSeconds;
        GameLog logger;
};

#endif