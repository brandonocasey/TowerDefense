#ifndef SETTINGS_H
#define SETTINGS_H

#include "utils.h"
#include "BaseGameState.h"
#include "MenuItem.h"

class Settings : public BaseGameState
{
    public:
        void Init();
        void Cleanup();

        void Pause();
        void Resume();

        void HandleEvents(GameEngine* game);
        void Update(GameEngine* game);
        void Draw(GameEngine* game);

        static Settings* Instance()
        {
            return &m_Settings;
        }

    protected:
        Settings() { }

    private:
        static Settings m_Settings;
        std::vector<MenuItem*> m_vMenuItems;
        GameLog logger;
};

#endif