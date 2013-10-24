#include "MainMenu.h"

// Singleton Yeah!
MainMenu MainMenu::m_MainMenu;

void MainMenu::Init()
{
    m_sName = "MainMenu";
    logger.Init(LOGFILE, m_sName, 5);

    m_vMenuItems.push_back( MenuItem(1, 1, 100, 100, "New Game") );
    m_vMenuItems.push_back( MenuItem(1, 1, 1, 1, "Load Game") );
    m_vMenuItems.push_back( MenuItem(1, 1, 1, 1, "Settings") );
    m_vMenuItems.push_back( MenuItem(1, 1, 1, 1, "Quit") );

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
    int mouse_x = 0;
    int mouse_y = 0;
    SDL_GetMouseState(&mouse_x, &mouse_y);

     for(MenuItem it : m_vMenuItems)
    {
        if( CheckMouse(it, mouse_x, mouse_y) )
        {
            //logger.Log( "Mouse is currenty over " + it.GetName() );
            //it.MouseOver();
        }
    }
	if (SDL_PollEvent(&event))
    {
		switch (event.type)
        {
			case SDL_QUIT:
				game->Quit();
				break;

            case SDL_MOUSEBUTTONDOWN:
                for(MenuItem it : m_vMenuItems)
                {
                    if( CheckMouse(it, mouse_x, mouse_y) )
                    {
                        logger.Log( "Mouse clicked " + it.GetName() );
                        //it.Action();
                    }
                }
                break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
                {
					case SDLK_ESCAPE:
                        game->Quit();
						//game->PopState();
						break;
				}
				break;
		}
	}
}

bool MainMenu::CheckMouse(MenuItem box, int mouse_x, int mouse_y)
{
    SDL_Rect collision = box.GetCollisionRect();

    if( ( mouse_x > collision.x ) && ( mouse_x < collision.x + collision.w ) && ( mouse_y > collision.y ) && ( mouse_y < collision.y + collision.h ) )
    {
        return true;
    }

    return false;
}

void MainMenu::Update(GameEngine* game) 
{
    // vectors start at 1
    for(MenuItem it : m_vMenuItems)
    {
        //logger.Log("Update Menu Items: " + it.GetName() );
    }
}

void MainMenu::Draw(GameEngine* game) 
{
    for(MenuItem it : m_vMenuItems)
    {
        //logger.Log("Draw Menu Items: " + it.GetName() );
    }
}