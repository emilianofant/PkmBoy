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

void AssetManager::CreateMapObject(Vector2D pos, std::string id)
{
  auto& mapObject(manager->addEntity());
  mapObject.addComponent<TransformComponent>(pos.x, pos.y, 32, 16, 2);
	mapObject.addComponent<SpriteComponent>("map_objects", 0, 32, 16, 32);
	mapObject.addComponent<ColliderComponent>(id, pos.x, pos.y, 32, 16);
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
