#pragma once

#include "classes/GameEngine.h"         // Our top level Game Engine Class
#include "classes/GameLog.h"            // The Log for our game

#include "base_classes/BaseGameState.h"
#include "base_classes/BaseObject.h"
#include "base_classes/BaseStaticObject.h"

#include "helper_classes/AudioHelper.h"
#include "helper_classes/EventHelper.h"
#include "helper_classes/RenderHelper.h"
#include "helper_classes/SaveHelper.h"


#include <SDL2/SDL.h>			// SDL OpenGL Framework
#include <SDL2/SDL_image.h>		// An SDL2 extension that enables different image formats
#include <SDL2/SDL_mixer.h>		// An SDL2 Extension that enables different Audio Formats
#include <SDL2/SDL_net.h>		// An SDL2 extension that enables easier network programming
#include <SDL2/SDL_ttf.h>		// An SDL2 extension that enables fonts
#include <iostream>				// cout, cin, etc
#include <ostream>				// control what output stream to print to, an actual LOG file , STDOUT, etc
#include <string>				// Enable string data types
#include <vector>               // Enable Vectors

// Map Loader
#include <TmxParser/Tmx.h>

// Callback functions for menu items
#include <boost/function.hpp>   // Allow function references to be accepted as arguments
#include <boost/bind.hpp>       // Allow function references to be passed as arguments


// Safely delete pointers, arrays of points, and release memory and such from the heap (dynamic memory)
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=nullptr; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=nullptr; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=nullptr; } }
#endif

// Constants
#define LOG_FILE std::cout
#define MENU_FONT "fonts/SourceSansPro-Regular.ttf"
#define LOG_LEVEL 5
#define GAME_NAME "Last Bastion"
