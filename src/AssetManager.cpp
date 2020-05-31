#include "TextureManager.h"
#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::CreatePlayer(Vector2D pos, std::string id)
{
  auto& player(manager->addEntity());
  // @todo: the scale value should be globally defined
  player.addComponent<TransformComponent>(pos.x, pos.y, 2);
	player.addComponent<SpriteComponent>(id, true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(Game::groupPlayers);
}

void AssetManager::CreateMapObject(Vector2D pos, spriteType_t spr, int sc)
{
  int sprXpos = spritesInfo[spr].xPos * 16; 
  int sprYpos = spritesInfo[spr].yPos * 16; 
  int sprH = spritesInfo[spr].height;
  int sprW = spritesInfo[spr].width;

  auto& mapObject(manager->addEntity());
  mapObject.addComponent<TransformComponent>(pos.x, pos.y, sprH, sprW, sc);
	mapObject.addComponent<SpriteComponent>("map_objects", sprXpos, sprYpos, sprH, sprW);
	mapObject.addComponent<ColliderComponent>("map_objects", pos.x, pos.y, sprH, sprW);
	mapObject.addGroup(Game::groupMapObjects);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
  textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
  return textures[id];
}
