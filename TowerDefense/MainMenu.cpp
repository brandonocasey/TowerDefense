#include "MainMenu.h"
#include "MenuItem.h"
// Singleton Yeah!
MainMenu MainMenu::m_MainMenu;

void MainMenu::Init()
{
    m_sName = "MainMenu";
    logger.Init(LOGFILE, m_sName, 5);



    m_vMenuItems.push_back( new MenuItem(100, 100, 100, 100, "New Game") );
    m_vMenuItems.push_back( new MenuItem(100, 200, 100, 100, "Load Game") );
    m_vMenuItems.push_back( new MenuItem(100, 300, 100, 100, "Settings") );
    m_vMenuItems.push_back( new MenuItem(100, 400, 100, 100, "Quit") );
    //m_vMenuItems.push_back( new MenuItem(100, 400, 100, 100, "Quit", &MainMenu::Quit) );
}

void MainMenu::Cleanup()
{
    while( ! m_vMenuItems.empty() )
    {
        m_vMenuItems.back()->Cleanup();
        m_vMenuItems.pop_back();
    }
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

            case SDL_MOUSEBUTTONDOWN:
                for(MenuItem *it : m_vMenuItems)
                {
                    // If in selected state then we know that they clicked
                    if( it->IsSelected() )
                    {
                        logger.Log( "Mouse clicked " + it->GetName() );
                        it->Action(game);
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

void MainMenu::Quit(GameEngine* game)
{
    game->Quit();
}

void MainMenu::Update(GameEngine* game)
{
     for(MenuItem *it : m_vMenuItems)
    {
        int mouse_x = 0;
        int mouse_y = 0;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        // if our mouse is not over the button but set to hover state
        // unselect it
        if( ! it->CheckMouse(mouse_x, mouse_y) && it->IsSelected() )
        {
            logger.Log("Mouse has left " + it->GetName() );
            it->UnSelected();
        }
        // Otherwise if it is hovered over, set to selected state
        if( it->CheckMouse(mouse_x, mouse_y ) )
        {
            logger.Log("Mouse has Entered "  + it->GetName() );
            it->Selected();
        }
    }
}

void MainMenu::Draw(GameEngine* game)
{
    for(MenuItem *it : m_vMenuItems)
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(game->m_cRenderer, it->m_cCurrentSurface);
        SDL_Rect* current_position = &it->GetCollisionRect();
        SDL_RenderCopy(game->m_cRenderer, texture, NULL, current_position );
        SDL_RenderPresent(game->m_cRenderer);

        SDL_DestroyTexture(texture);
    }
}
