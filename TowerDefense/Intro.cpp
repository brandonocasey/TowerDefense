#include "Intro.h"

const int LOGO_SECONDS = 5;
// Singleton Yeah!
Intro Intro::m_Intro;

void Intro::Init()
{
    m_sName = "Intro";
    m_cCurrentTexture = nullptr;
    m_iCountdownStart = 0;
    m_iCountdownTotalSeconds = 0;


    logger.Init(LOGFILE, m_sName, 5);

    m_vBackgrounds.push_back( "img/logo.jpg" );

    // make sure to clean up
	//SDL_Surface* temp = SDL_LoadBMP("menu.bmp");

	//bg = SDL_DisplayFormat(temp);

	//SDL_FreeSurface(temp);

	//printf("CMenuState Init\n");
}

void Intro::Cleanup()
{
    // Free the memory for all of the images.

    if( m_cCurrentTexture != nullptr )
    {
        SDL_DestroyTexture(m_cCurrentTexture);
        m_cCurrentTexture = nullptr;
    }
}

void Intro::Pause()
{
    // Not Needed for this state
}

void Intro::Resume()
{
    // Not Needed for this state
}

void Intro::HandleEvents(GameEngine* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
    {
		switch (event.type)
        {
            // If they hit the close window button
			case SDL_QUIT:
				game->Quit();
				break;

            // If they hit a key we change to the press start state
			case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
                logger.Log("User has skipped intro");
			    game->ChangeState(MainMenu::Instance());
				break;
		}
	}
}

void Intro::StartTimer()
{
    m_iCountdownStart = SDL_GetTicks();
    m_iCountdownTotalSeconds = LOGO_SECONDS * 1000;


    m_iCountdownTotalSeconds += m_iCountdownStart;

    logger.Log("Started a timer with start milli seconds of " + std::to_string(m_iCountdownStart) + " and end of " + std::to_string(m_iCountdownTotalSeconds) );
}

bool Intro::TimerOver()
{
    if( m_iCountdownTotalSeconds > m_iCountdownStart && m_iCountdownStart != 0 )
    {
        return false;
    }

    return true;
}

void Intro::Update(GameEngine* game)
{
    // Count Down to 0 for image change
    // Draw the current image
    if( TimerOver() && ! m_vBackgrounds.empty() )
    {
        if( m_cCurrentTexture != nullptr )
        {
            SDL_DestroyTexture(m_cCurrentTexture);
            m_cCurrentTexture = nullptr;
        }
        m_cCurrentTexture = IMG_LoadTexture( game->m_cRenderer, m_vBackgrounds.back().c_str() );
        if( m_cCurrentTexture != nullptr )
        {
            logger.Log( "Changed the background image to " + m_vBackgrounds.back() );
            m_vBackgrounds.pop_back();
        }
        else
        {
            logger.LogError( "LoadTexture Failed for image " + m_vBackgrounds.back() );
        }
        StartTimer();
    }
    else if( TimerOver() &&  m_vBackgrounds.empty() )
    {
        game->ChangeState( MainMenu::Instance() );
    }
    m_iCountdownStart = SDL_GetTicks();

}

void Intro::Draw(GameEngine* game)
{
    int w;
    int h;
    if( m_cCurrentTexture != nullptr )
    {
        SDL_QueryTexture(m_cCurrentTexture, NULL, NULL, &w, &h);
        SDL_Rect destination;

        // Get current screen size
        //SDL_RendererInfo* render_info = nullptr;

        //int result = SDL_GetRendererInfo(game->m_cRenderer, render_info);

        //if( result == 0 )
        //{
            //int x = render_info->max_texture_width / 2 - w / 2;
	        //int y = render_info->max_texture_height / 2 - h / 2;
            int x = 0;
            int y = 0;

            destination.x = x;
            destination.y = y;

	        destination.w = w;
	        destination.h = h;
            logger.Log("Attempting to render an image at x = " + std::to_string(x) + " y = " + std::to_string(y) + " h = " + std::to_string(h) + " w = " + std::to_string(w));
	        SDL_RenderCopy(game->m_cRenderer, m_cCurrentTexture, NULL, &destination);
            SDL_RenderPresent(game->m_cRenderer);
            SDL_DestroyTexture(m_cCurrentTexture);
            m_cCurrentTexture = nullptr;

        //}
        //else
        //{
        //    logger.LogError("SDL_GetRenderInfo returned a nullptr with error" + std::string(SDL_GetError()) );
        //}
    }
}
