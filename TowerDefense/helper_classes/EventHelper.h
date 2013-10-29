#pragma once
#include "../Utils.h"

// Tell the state which controls to use
class EventHelper
{
    public:
        void Init();
        // Quit the game if we see SDL_Quit
        // boost::function<int()> quit_pointer = &GameEngine::Quit;
        // SDL_AddEventWatch(SLD_EventFilter quit_pointer,
};
