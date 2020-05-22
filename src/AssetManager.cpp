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

void AssetManager::AddTexture(std::string id, const char* path)
{
  textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
  return textures[id];
}
