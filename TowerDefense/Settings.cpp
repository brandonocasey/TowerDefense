#include "Settings.h"

// Singleton Yeah!
Settings Settings::m_Settings;

void Settings::Init()
{
    m_sName = "Settings";
    logger.Init(LOGFILE, m_sName, 5);



    m_vMenuItems.push_back( new MenuItem("Toggle Fullscreen", boost::bind(&Settings::ToggleFullscreenCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Master Volume", boost::bind(&Settings::MasterVolumeCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Music Volume", boost::bind(&Settings::MusicVolumeCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Sound Volume", boost::bind(&Settings::SoundVolumeCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Brightness", boost::bind(&Settings::BrightnessCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Clear Save Data", boost::bind(&Settings::ClearSaveDataCallback, this, _1) ) );
    m_vMenuItems.push_back( new MenuItem("Resize Window", boost::bind(&Settings::ResizeWindowCallback, this, _1) ) );


    m_vMenuItems.push_back( new MenuItem("Back", boost::bind(&Settings::BackCallback, this, _1) ) );

}

void Settings::ClearSaveDataCallback(GameEngine* game)
{
}

void Settings::MasterVolumeCallback(GameEngine* game)
{
}
void Settings::SoundVolumeCallback(GameEngine* game)
{
}
void Settings::MusicVolumeCallback(GameEngine* game)
{
}
void Settings::BrightnessCallback(GameEngine* game)
{
}
void Settings::ToggleFullscreenCallback(GameEngine* game)
{
    game->ToggleFullScreen();
}
void Settings::ResizeWindowCallback(GameEngine* game)
{
}

void Settings::BackCallback(GameEngine* game)
{
    game->ClearScreen();
    game->PopState();
}
void Settings::Cleanup()
{
    while( ! m_vMenuItems.empty() )
    {
        m_vMenuItems.back()->Cleanup();
        m_vMenuItems.pop_back();
    }
}

void Settings::Pause(GameEngine* game)
{
    Cleanup();
    game->ClearScreen();
}

void Settings::Resume(GameEngine* game)
{
    Init();
}

void Settings::HandleEvents(GameEngine* game)
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

						BackCallback(game);
						break;
				}
				break;
		}
	}
}

void Settings::Update(GameEngine* game)
{
     for(MenuItem *it : m_vMenuItems)
    {
        it->Update(game);
    }
}

void Settings::Draw(GameEngine* game)
{
    // Get Screen height / Menu Items
    // Get Screen width / 2

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
