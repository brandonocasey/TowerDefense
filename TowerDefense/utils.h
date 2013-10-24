#ifndef UTILS_H
#define UTILS_H

#include "GameLog.h"
#include <SDL2/SDL.h>			// SDL OpenGL Framework
#include <SDL2/SDL_image.h>		// An SDL2 extension that enables different image formats
#include <SDL2/SDL_mixer.h>		// An SDL2 Extension that enables differnt Audio Formats
#include <SDL2/SDL_net.h>		// An SDL2 extension that enables easier network programming
#include <SDL2/SDL_ttf.h>		// An SDL2 extension that enables fonts
#include <iostream>				// cout, cin, etc
#include <ostream>				// control what output stream to print to, an actual LOG file , STDOUT, etc
#include <string>				// Enable string data types
#include <vector>               // Enable Vectors

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
#define LOGFILE std::cout

#endif