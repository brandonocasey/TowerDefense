#include "GameEngine.h"
#include "BaseGameState.h" // This is included here so that we can use it
// Tutorial on showing current FPS etc
//http://lazyfoo.net/SDL_tutorials/lesson15/index.php

/**
 * This function initializes the game engine
 * @param  title      The title for the games window
 * @param  width      the width of our game screen
 * @param  height     the height of our game screen
 * @param  fullscreen true for fullscreen window
 * @return            0 if everything was successful
 */
int GameEngine::Init(const char* title, int width = 400, int height = 400, bool fullscreen = false)
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    m_iScreenWidth = width;
    m_iScreenHeight = height;

    logger.Init(LOGFILE, "GameEngine" , LOG_LEVEL);
    m_bFullscreen = nullptr;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logger.LogError( std::string("SDL_Init: ") + SDL_GetError() );
        return 1;
    }
    else
    {
        logger.Log("SDL_Init: SDL_Init_Everything work OK");
    }

    m_cWindow = nullptr;
    m_cWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if( m_cWindow == nullptr )
    {
        logger.LogError( std::string("SDL_CreateWindow: ") + SDL_GetError() );
        return 2;
    }
    else
    {
        logger.Log("SDL_CreateWindow was successful");
    }

    m_cRenderer = nullptr;
    m_cRenderer = SDL_CreateRenderer(m_cWindow, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
    if( m_cRenderer == nullptr )
    {
        logger.LogError( std::string("SDL_CreateRenderer: ") + SDL_GetError() );
        return 3;
    }
    else
    {
        logger.Log("SDL_CreateRenderer was successful");
    }

    int img_flags = IMG_INIT_JPG|IMG_INIT_PNG;
    if ((IMG_Init(img_flags) != img_flags))
    {
		logger.LogError("IMG_Init failed to init jpeg with error "  + std::string(SDL_GetError()) );
        return 4;
	}
    else
    {
        logger.Log("IMG_Init was successful!");
    }

    if (TTF_Init() == -1)
    {
		logger.LogError("TTF_Init Failed with error: "  + std::string(TTF_GetError()) );
        return 5;
	}
    else
    {
        logger.Log("TTF_Init was successful!");
    }

    // Setup full screen if we need to
    ToggleFullScreen(fullscreen);

    // Clear the Screen to black and present it
    ClearScreen();

    SDL_ShowCursor(1);


    m_bRunning = true;

    return 0;
}

/**
 * This function cleans up all of the resources that we create in init and
 * also cleans up all of our states
 */
void GameEngine::Cleanup()
{
    logger.Log("Attempting to cleanup all of the things in GameEngine");
    while( ! states.empty() )
    {
        logger.Log("Calling Cleanup function for " + states.back()->m_sName);
        states.back()->Cleanup();
        states.pop_back();
    }

    if( m_bFullscreen )
    {
        ToggleFullScreen();
    }

    SDL_DestroyRenderer(m_cRenderer);
    SDL_DestroyWindow(m_cWindow);

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

}

/**
 * Change the games state completely, by getting rid of current states and
 * cleaning them up. Followed by pushing a state and running its init function.
 * @param state The state we want to go to
 */
void GameEngine::ChangeState(BaseGameState* state)
{
    if( ! states.empty() )
    {
        states.back()->Cleanup();
        states.pop_back();
        ClearScreen();
    }

    states.push_back( state );
    states.back()->Init();
    logger.Log("Changing State to " + state->m_sName);
}

/**
 * Push a state onto the stack and pause the current state
 * @param state The state to push
 */
void GameEngine::PushState(BaseGameState* state)
{
    logger.Log("Pushing a new State " + state->m_sName);
    // Pause the current State
    if ( !states.empty() )
    {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();

}

/**
 * Pop the current state off of the stack and and resume the previous state
 */
void GameEngine::PopState()
{
    // cleanup the current state
	if ( !states.empty() )
    {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() )
    {
		states.back()->Resume();
	}
    else
    {
        logger.LogError("Attempted to pop off a state when there are none");
    }
    logger.Log("Getting rid of the current state" + states.back()->m_sName);

}

/**
 * Resize the game window, for use with the setting menu
 * @param width  width of the screen
 * @param height height of the screen
 */
void GameEngine::ResizeWindow(int width, int height)
{
    SDL_SetWindowSize(m_cWindow, width, height);
    m_iScreenWidth = width;
    m_iScreenHeight = height;
    ToggleFullScreen();
}

/**
 * Have the current state handle events
 */
void GameEngine::HandleEvents()
{
    if( ! states.empty() && m_bRunning )
    {
        states.back()->HandleEvents(this);
    }
}

/**
 * Have the current state update
 */
void GameEngine::Update()
{
    if( ! states.empty() && m_bRunning )
    {
        states.back()->Update(this);
    }
}

/**
 * Have the current state draw itself
 */
void GameEngine::Draw()
{
    if( ! states.empty() && m_bRunning )
    {
        states.back()->Draw(this);
    }
}


/**
 * Clear the screen with a black color
 */
void GameEngine::ClearScreen()
{
    SDL_SetRenderDrawColor(m_cRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_cRenderer);
    SDL_RenderPresent(m_cRenderer);
}

/**
 * Change the in game volume level
 * @param level The new level that the volume should be
 */
void GameEngine::ChangeVolumeLevel(int level)
{
    //Stub
}

/**
 * Change the brightness level of the game
 * @param level The brightness level that the game should now be
 */
void GameEngine::ChangeBrightness(int level)
{
    //Stub
}

/**
 * Clear all of the save data in the game, includes a pop up confirmation
 */
void GameEngine::ClearSaveData()
{
    // Stub
}

/**
 * Toggle fullscreen using the internal GameEngine Variable
 */
void GameEngine::ToggleFullScreen()
{
    logger.Log("Toggle Fullscreen");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(m_cRenderer, m_iScreenWidth, m_iScreenHeight);
    if( ! m_bFullscreen )
    {
        if( SDL_SetWindowFullscreen(m_cWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) )
        {
            m_bFullscreen = true;
            logger.LogError("Fullscreen successfully initialized");
        }
        else
        {
            logger.LogError("Turning Fullscreen On failed with error " + std::string(SDL_GetError()));
        }
    }
    else
    {
        if( SDL_SetWindowFullscreen(m_cWindow, SDL_FALSE) )
        {
            m_bFullscreen = false;
            logger.LogError("Fullscreen successfully turned off");
        }
        else
        {
            logger.LogError("Turning Fullscreen off failed with error " +  std::string(SDL_GetError()));
        }
    }
}

/**
 * Toggle fullscreen using the variable that is passed to us
 * @param fullscreen if true we want fullscreen on, otherwise it is off
 */
void GameEngine::ToggleFullScreen(bool fullscreen)
{
    if( fullscreen )
    {
        m_bFullscreen = false;
        ToggleFullScreen();
    }
    else
    {
        m_bFullscreen = true;
        ToggleFullScreen();
    }
}

/**
 * Returns the current status of the game
 * @return a bool indicating the current status of the game
 */
bool GameEngine::Running()
{
    return m_bRunning;
}

/**
 * Set the game status to false, meaning that the game should quit
 */
void GameEngine::Quit()
{
    logger.Log("Quit has been called");
    m_bRunning = false;
}

/**
 * Call all of the function that are state needs to run with
 */
void GameEngine::Run()
{
    this->HandleEvents();
    this->Update();
    this->Draw();
}

