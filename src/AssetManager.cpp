#include "AssetManager.h"
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

void AssetManager::CreateTrigger(triggerEnum_t tr, int sc)
{
  auto& trigger(manager->addEntity());
  trigger.addComponent<TransformComponent>(
    triggersDefinitions[tr].position.x,
    triggersDefinitions[tr].position.y,
    sc
  );
	trigger.addComponent<ColliderComponent>(
    "trigger",
    triggersDefinitions[tr].position.x,
    triggersDefinitions[tr].position.y,
    16 * sc
  );
  trigger.addComponent<TriggerComponent>(tr);

	trigger.addGroup(Game::groupTriggers);
}

void AssetManager::CreateDialogBox(int sc)
{
  int _scale = 2;
  SDL_Color black = { 15, 26, 15, 255 };

  auto& dialogBox(manager->addEntity());
  dialogBox.addComponent<GUI>(sc);
  dialogBox.getComponent<GUI>().CreateDialogBox();
  // Text Label component
  dialogBox.addComponent<GUILabel>(8 * _scale, 112 * _scale, "Gary, you can have\n\none too!", "pkmn", black);
	dialogBox.addGroup(Game::groupGui);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
  textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
  return textures[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}
