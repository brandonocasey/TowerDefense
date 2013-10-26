#include "GameEngine.h"
#include "Intro.h"
 
int main ( int argc, char** argv )
{
    GameEngine game;

    // initialize the engine, if there is an error return 1 for failure
    if( game.Init( "Tower Defense Test v1.0", 640, 640, false ) )
    {
        return 1;
    }
    
    // load the intro
    game.ChangeState( Intro::Instance() );

    // main loop
    while ( game.Running() )
    {
        game.Run();
    }

    // cleanup the engine
    game.Cleanup();
    return 0;
}
