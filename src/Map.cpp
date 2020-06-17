#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/Components.h"

extern Manager manager;

Map::Map()
{}

// @todo: validate if this is still valid.
Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
  scaledSize = ms * ts;
}

Map::~Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
  char c;
  std::fstream mapFile;
  mapFile.open(path);

  int srcX, srcY;

  for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      mapFile.get(c);
      srcY = atoi(&c) * tileSize;
      mapFile.get(c);
      srcX = atoi(&c) * tileSize;
      AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
      mapFile.ignore(); // Ignore commas from .map file
    }
  }

  mapFile.ignore();

  for (int y = 0; y < sizeY; y++)
  {
    for (int x = 0; x < sizeX; x++)
    {
      mapFile.get(c);
      if (c == '1')
      {
        //collision
        auto &tcol(manager.addEntity());
        tcol.addComponent<ColliderComponent>("wall", x * scaledSize, y * scaledSize, scaledSize);
        tcol.addGroup(Game::groupColliders);
      }
      mapFile.ignore();
    }
  }

  mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
  tile.addGroup(Game::groupMap);
}

void Map::SetMap(mapData_t mapId)
{
  std::string path = mapData[mapId].mapPath;
  int sizeX= mapData[mapId].width;
  int sizeY = mapData[mapId].height;

  tileSize = mapData[mapId].tileSize;
  mapScale = 2;

  // @todo: refactor al scaling calcules
  scaledSize = tileSize * mapScale;
  texID = mapData[mapId].id;

  LoadMap(path, sizeX, sizeY);

  // Set player's position in the new map
  Game::player->getComponent<TransformComponent>().setNewPosition(mapData[mapId].playerInitPosition);
}

void Map::ChangeMap(mapData_t mapId)
{
  _ClearMapData();
  SetMap(mapId);
}

void Map::_ClearMapData()
{
  auto& tiles(manager.getGroup(Game::groupMap));
  auto& colliders(manager.getGroup(Game::groupColliders));
  auto& mapObjects(manager.getGroup(Game::groupMapObjects));
  auto& triggers(manager.getGroup(Game::groupTriggers));

  for (auto& ti : tiles) {
  	ti->destroy();
  }

  for (auto& c : colliders) {
  	if(c->getComponent<ColliderComponent>().tag == "wall") {
  		c->destroy();
  	}
  }

  for (auto& tr : triggers) {
  	tr->destroy();
  }

  for (auto& o : mapObjects) {
  	o->destroy();
  }
}
