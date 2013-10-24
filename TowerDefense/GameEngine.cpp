#include "GameEngine.h"
#include "BaseGameState.h"

int GameEngine::Init(const char* title, int width = 400, int height = 400, bool fullscreen = false)
{
    m_iScreenWidth = width;
    m_iScreenHeight = height;

    logger.Init(LOGFILE, "GameEngine" , 5);
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
    m_cRenderer = SDL_CreateRenderer(m_cWindow, -1, SDL_RENDERER_PRESENTVSYNC);
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


    //SDL_DestroyTexture(tex);

    SDL_DestroyRenderer(m_cRenderer);
    SDL_DestroyWindow(m_cWindow);

    IMG_Quit();
    SDL_Quit();
}

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

void GameEngine::ResizeWindow(int width, int height)
{

    SDL_SetWindowSize(m_cWindow, width, height);
    m_iScreenWidth = width;
    m_iScreenHeight = height;
}
void GameEngine::HandleEvents()
{
    if( ! states.empty() && m_bRunning )
    {
        states.back()->HandleEvents(this);
    }
}

void GameEngine::Update()
{
    if( ! states.empty() && m_bRunning )
    {
        states.back()->Update(this);
    }
}

void GameEngine::ClearScreen()
{
    SDL_SetRenderDrawColor(m_cRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_cRenderer);
    SDL_RenderPresent(m_cRenderer);
}

void GameEngine::ChangeVolumeLevel(int level)
{
    //Stub
}

void GameEngine::ChangeBrightness(int level)
{
    //Stub
}

void GameEngine::ClearSaveData()
{
    // Stub
}

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

void GameEngine::ToggleFullScreen(bool fullscreen)
{
    logger.Log("Toggle Fullscreen");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(m_cRenderer, m_iScreenWidth, m_iScreenHeight);
    if( fullscreen )
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

void GameEngine::Draw()
{
    if( ! states.empty() && m_bRunning )
    {
        states.back()->Draw(this);
    }
}

bool GameEngine::Running()
{
    return m_bRunning;
}

void GameEngine::Quit()
{
    logger.Log("Quit has been called");
    m_bRunning = false;
}

void GameEngine::Run()
{
    this->HandleEvents();
    this->Update();
    this->Draw();
}

