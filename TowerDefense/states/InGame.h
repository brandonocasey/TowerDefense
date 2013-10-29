#pragma once

#include "..\Utils.h"

class Tower;
// How do I pass a map here?
class InGame : public BaseGameState
{
    public:
        void Init();
        void Cleanup();

        void Pause(GameEngine* game);
        void Resume(GameEngine* game);

        void HandleEvents(GameEngine* game);
        void Update(GameEngine* game);
        void Draw(GameEngine* game);

        void DrawTowers(GameEngine* game);
        void InGame::DrawMap(GameEngine* game);

        void LoadMap(std::string map_location);
        static InGame* Instance()
        {
            return &m_InGame;
        }

    protected:
        InGame() { }

    private:
        Tmx::Map *m_cMap;
        static InGame m_InGame;
        GameLog *logger;
        bool m_bMapDrawn;
         std::vector<Tower*> m_vTowerList;
};
