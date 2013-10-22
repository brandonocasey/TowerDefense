#include "GameEngine.h"
 
int main ( int argc, char** argv )
{
    GameEngine game;

    // initialize the engine
    game.Init( "Engine Test v1.0", 400, 400, false );

    return 1;
    // load the intro
/*    game.ChangeState( IntroState::Instance() );

    // main loop
    while ( game.Running() )
    {
        game.Run();
    }

    // cleanup the engine
    game.Cleanup();
    return 0;
    */
}
