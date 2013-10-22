#include <SDL2/SDL.h>			// SDL OpenGL Framework
#include <SDL2/SDL_image.h>		// An SDL2 extension that enables different image formats
#include <iostream>				// cout, cin, etc
#include <ostream>				// control what output stream to print to, an actual LOG file , STDOUT, etc
#include <string>				// Enable string data types

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

// Screen Size Constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE     = 40;