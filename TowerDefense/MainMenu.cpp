#include "MainMenu.h"

// Singleton Yeah!
MainMenu MainMenu::m_MainMenu;

void MainMenu::Init()
{
    m_sName = "MainMenu";
    logger.Init(LOGFILE, m_sName, 5);
	//SDL_Surface* temp = SDL_LoadBMP("menu.bmp");

	//bg = SDL_DisplayFormat(temp);

	//SDL_FreeSurface(temp);

	//printf("CMenuState Init\n");
}

void MainMenu::Cleanup()
{
}

void MainMenu::Pause()
{
}

void MainMenu::Resume()
{
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

}

void MainMenu::Draw(GameEngine* game) 
{
}