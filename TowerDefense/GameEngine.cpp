#include "GameEngine.h"
#include "BaseGameState.h"

int GameEngine::Init(const char* title, int width, int height, bool fullscreen)
{
    logger.Init(std::cout, "GameEngine" , 5);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logger.LogError( std::string("SDL_Init: ") + SDL_GetError() );
        return 1;
    }
    else
    {
        logger.Log("SDL_Init: SDL_Init_Everything work OK");
    }



    m_bRunning = true;

    return 0;
}

void GameEngine::Cleanup()
{
    while( ! states.empty() )
    {
        states.back()->Cleanup();
        states.pop_back();
    }
}

void GameEngine::ChangeState(BaseGameState* state)
{
    states.push_back( state );
    states.back()->Init();
}

void GameEngine::PushState(BaseGameState* state)
{
}

void GameEngine::PopState()
{
}

void GameEngine::HandleEvents()
{
    states.back()->HandleEvents(this);
}

void GameEngine::Update()
{
    states.back()->Update(this);
}

void GameEngine::Draw()
{
    states.back()->Draw(this);
}

bool GameEngine::Running()
{
    return m_bRunning;
}

void GameEngine::Quit()
{
    m_bRunning = false;
}

void GameEngine::Run()
{
    HandleEvents();
    Draw();
    Update();
}

