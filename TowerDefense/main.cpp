#include "GameEngine.h"
#include "Intro.h"
 
int main ( int argc, char** argv )
{
    GameEngine game;

    // initialize the engine, if there is an error return 1 for failure
    if( game.Init( "Engine Test v1.0", 600, 600, true ) )
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
