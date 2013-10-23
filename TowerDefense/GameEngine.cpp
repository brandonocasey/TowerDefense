#include "GameEngine.h"
#include "BaseGameState.h"

int GameEngine::Init(const char* title, int width = 400, int height = 400, bool fullscreen = false)
{
    logger.Init(LOGFILE, "GameEngine" , 5);
    m_bFullscreen = fullscreen;

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
    m_cWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
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
    m_cRenderer = SDL_CreateRenderer(m_cWindow, -1, SDL_WINDOW_OPENGL | SDL_RENDERER_PRESENTVSYNC);
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

    ToggleFullScreen();

    // Clear the Screen to black and present it
    ClearScreen();
    

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
    logger.Log( "Attempting to resize the window to width = " + std::to_string(width) + " and height = " + std::to_string(height));

    SDL_SetWindowSize(m_cWindow, width, height);
}
void GameEngine::HandleEvents()
{
    if( ! states.empty() )
    {
        states.back()->HandleEvents(this);
    }
}

void GameEngine::Update()
{
    if( ! states.empty() )
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

void GameEngine::ToggleFullScreen()
{
    logger.Log("Toggle Fullscreen");
    int result = 0;
    if( ! m_bFullscreen )
    {
        result = SDL_SetWindowFullscreen(m_cWindow, SDL_WINDOW_FULLSCREEN);
        if( result == 0 )
        {
            m_bFullscreen = true;
        }
        else
        {
            logger.LogError("Turning Fullscreen On failed with error " + std::string(SDL_GetError()));
        }
    }
    else
    {
        result = SDL_SetWindowFullscreen(m_cWindow, SDL_FALSE);
        if( result == 0 )
        {
            m_bFullscreen = false;
        }
        else
        {
            logger.LogError("Turning Fullscreen off failed with error " +  std::string(SDL_GetError()));
        }
    }

}

void GameEngine::Draw()
{
    if( ! states.empty() )
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

