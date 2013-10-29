#include "MainMenu.h"
#include "../classes/MenuItem.h"
// Singleton Yeah!
MainMenu MainMenu::m_MainMenu;

void MainMenu::Init(GameEngine* game)
{
    m_sName = "MainMenu";
    logger = logger->GetLogger(m_sName);

    m_vMenuItems.push_back( new MenuItem("New Game", boost::bind(&MainMenu::NewGameCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Load Game", boost::bind(&MainMenu::LoadGameCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Settings", boost::bind(&MainMenu::SettingsCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Quit", boost::bind(&MainMenu::QuitCallback, this, _1) ) );

}

void MainMenu::Cleanup(GameEngine* game)
{
    while( ! m_vMenuItems.empty() )
    {
        m_vMenuItems.back()->Cleanup();
        m_vMenuItems.pop_back();
    }
}

void MainMenu::Pause(GameEngine* game)
{
    Cleanup(game);
    game->ClearScreen();
}

void MainMenu::Resume(GameEngine* game)
{
    Init(game);
}

void MainMenu::QuitCallback(GameEngine* game)
{
    game->Quit();
}

void MainMenu::LoadGameCallback(GameEngine* game)
{
    game->Quit();
}

void MainMenu::NewGameCallback(GameEngine* game)
{
    //game->ChangeState( NewGame::Instance() );
}

void MainMenu::SettingsCallback(GameEngine* game)
{
    game->PushState( Settings::Instance() );
}


void MainMenu::HandleEvents(GameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
    {
		switch (event.type)
        {
			case SDL_QUIT:
				game->Quit();
				break;

            case SDL_MOUSEBUTTONDOWN:
                for(MenuItem *it : m_vMenuItems)
                {
                    it->Callback(game);
                }
                break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
                {
					case SDLK_ESCAPE:

						game->PopState();
						break;
				}
				break;
		}
	}
}

void MainMenu::Update(GameEngine* game)
{
     for(MenuItem *it : m_vMenuItems)
    {
        it->Update(game);
    }
}

void MainMenu::Draw(GameEngine* game)
{

    int screen_width = 0;
    int screen_height = 0;

    game->GetWindowSize( &screen_width, &screen_height );

    int x = 0;
    int y = 0;

    for(MenuItem *it : m_vMenuItems)
    {
        x = (screen_width /2) - (it->GetWidth() /2);
        y += it->GetHeight();
        it->Draw(game, x, y);
    }

    SDL_RenderPresent(game->m_cRenderer);
}
