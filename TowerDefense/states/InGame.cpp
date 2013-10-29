#include "InGame.h"


InGame InGame::m_InGame;

void InGame::Init(GameEngine* game)
{
    m_sName = "InGame";
    logger = logger->GetLogger(m_sName);
    m_cMap = nullptr;

    m_bMapDrawn = false;
    m_cMap = new Tmx::Map();

    LoadGame("./assets/maps/level_1.tmx");

}

void InGame::Cleanup(GameEngine* game)
{

}

void InGame::Pause(GameEngine* game)
{

}
void InGame::Resume(GameEngine* game)
{

}

void InGame::HandleEvents(GameEngine* game)
{
    SDL_Event event;

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:

                break;
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
void InGame::Update(GameEngine* game)
{
    // Map Collision

    //Monster Movement A*

    // Tower Attacks ??

    // Current Cursor

    // Time to Wave

    //

}
void InGame::Draw(GameEngine* game)
{
    DrawMap(game);
    DrawTowers(game);
    // DrawPlayer(game);
    // DrawUI(game);
}

void InGame::DrawTowers(GameEngine* game)
{
    for(Tower* it : m_vTowerList )
    {
        //m_vTowerList.back()->Draw(game);
    }
}

void InGame::DrawMap(GameEngine* game)
{
    // current collision array
    // spawn
    // waypoint
    // goal

    if( ! m_bMapDrawn )
    {
        logger->Log("Drawing Map");
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
                    destination.x = x* destination.w;
                    destination.y = y* destination.h;

                    std::string tile_source = tileset->GetImage()->GetSource();

                    int last_slash = tile_source.find_last_of("/");

                    if( last_slash > 0 )
                    {
                        tile_source = tile_source.substr(last_slash+1);
                    }

                    std::string sprites = SPRITES_FOLDER;
                    tile_source = sprites + tile_source;
                    SDL_Texture* texture = IMG_LoadTexture( game->m_cRenderer, tile_source.c_str()  );
                    // load texture

                    SDL_RenderCopy(game->m_cRenderer, texture, NULL, &destination);
                    SDL_RenderPresent(game->m_cRenderer);
                }
            }
        }
        m_bMapDrawn = true;
    }
//    SDL_RenderPresent(game->m_cRenderer);
 //   SDL_DestroyTexture(texture);
 //   texture = nullptr;
}

void InGame::LoadGame(std::string map_location)
{
    logger->Log("Attempting to parse map located at " + map_location);
    m_cMap->ParseFile(map_location);

    if (m_cMap->HasError())
    {
        logger->LogError("error code: " +  m_cMap->GetErrorCode());
        logger->LogError("error text: " +  m_cMap->GetErrorText());
    }
    else
    {
        logger->Log("Successfully loaded map located at " + map_location);
    }

}
