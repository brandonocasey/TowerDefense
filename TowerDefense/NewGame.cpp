#include "NewGame.h"


NewGame NewGame::m_NewGame;

void NewGame::Init()
{
    m_sName = "NewGame";
    logger.Init(LOGFILE, m_sName, 5);
    m_cMap = nullptr;

    m_cMap = new Tmx::Map();

    LoadMap("./maps/level_1.tmx");

}

void NewGame::Cleanup()
{

}

void NewGame::Pause(GameEngine* game)
{

}
void NewGame::Resume(GameEngine* game)
{

}

void NewGame::HandleEvents(GameEngine* game)
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

						game->Quit();
						break;
				}
				break;
		}
	}
}
void NewGame::Update(GameEngine* game)
{

}
void NewGame::Draw(GameEngine* game)
{
    DrawMap(game);
}


void NewGame::DrawMap(GameEngine* game)
{
    // current collision array
    // spawn
    // waypoint
    // goal


    for (int i = 0; i < m_cMap->GetNumLayers(); ++i)
    {
		const Tmx::Layer *layer = m_cMap->GetLayer(i);

		for (int y = 0; y < layer->GetHeight(); ++y)
        {
			for (int x = 0; x < layer->GetWidth(); ++x)
            {
				// Find a tileset for that id.
				const Tmx::Tileset *tileset = m_cMap->GetTileset(layer->GetTile(x,y).tilesetId);
				
               // const Tmx::Tile *tile = tileset->GetTile(tile_id);
               // const Tmx::PropertySet properties = tile->GetProperties();
                SDL_Rect destination;

                destination.w = tileset->GetTileHeight();
                destination.h = tileset->GetTileWidth();
                destination.x = x*tileset->GetTileWidth();
                destination.y = y*tileset->GetTileHeight();

                std::string tile_source = tileset->GetImage()->GetSource();
                tile_source = tile_source.substr(3);
                logger.Log( "Found first tile image at " + tile_source);
                SDL_Texture* texture = IMG_LoadTexture( game->m_cRenderer, tile_source.c_str()  );
                // load texture

                SDL_RenderCopy(game->m_cRenderer, texture, NULL, &destination);
                SDL_RenderPresent(game->m_cRenderer);
            }
        }
    }
//    SDL_RenderPresent(game->m_cRenderer);
 //   SDL_DestroyTexture(texture);
 //   texture = nullptr;
}

void NewGame::LoadMap(std::string map_location)
{
    logger.Log("Attempting to parse map located at " + map_location);
    m_cMap->ParseFile(map_location);

    if (m_cMap->HasError())
    {
		logger.LogError("error code: " +  m_cMap->GetErrorCode());
		logger.LogError("error text: " +  m_cMap->GetErrorText());
	}
    else
    {
        logger.Log("Successfully loaded map located at " + map_location);
    }

}