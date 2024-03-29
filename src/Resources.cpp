#include "Map.h"
#include "Resources.h"
#include "../src/ECS/ECS.h"
#include "ECS/Components.h"

// @todo: move to global constant
int sc = 2;

void ShowDialogBox();
void ChangeMap_Indoor();
void ChangeMap_Outdoor();

spriteInfo_t spritesInfo[NONE] = {
  { MOBJ_PLANT, 0, 2, 32, 16 },   // Plant sprite.
  { MOBJ_LIBRARY, 5, 0, 32, 16 }	// Library sprite.
};

mapDataStruct_t mapData[MAP_NONE] = {
  {MAP_INDOOR, "house", "assets/map/house.map", 22, 20, 8, Vector2D(256,256)},
  {MAP_OUTDOOR, "outdoor", "assets/map/outdoor.map", 28, 26, 16, Vector2D(288,320)}
};

triggersDefinition_t triggersDefinitions[TRG_NONE] = {
  // MAP_OUTDOOR Triggers.
  {TRG_SHOW_DIALOGBOX, Vector2D(288, 352), sc, ShowDialogBox},
  {TRG_CHANGEMAP_TO_INDOOR, Vector2D(288, 288), sc, ChangeMap_Indoor},
  // MAP_INDOOR Triggers.
  {TRG_CHANGEMAP_TO_OUTDOOR, Vector2D(256,288), sc, ChangeMap_Outdoor}
};

// @todo: define callbacks in a specific Callbacks.cpp files
// or TriggersAction.cpp file.
void doSomething()
{
  std::cout << "do some callback!";
}

void ChangeMap_Indoor()
{
  Game::map->ChangeMap(MAP_INDOOR);

  Game::assets->CreateMapObject(Vector2D(64,96), MOBJ_PLANT, 2);
  Game::assets->CreateMapObject(Vector2D(96,96), MOBJ_LIBRARY, 2);
  Game::assets->CreateTrigger(TRG_CHANGEMAP_TO_OUTDOOR, sc);
}

void ChangeMap_Outdoor()
{
  Game::map->ChangeMap(MAP_OUTDOOR);
  Game::assets->CreateTrigger(TRG_CHANGEMAP_TO_INDOOR, sc);
}

void ShowDialogBox()
{
  // @todo: toggle the active flag
}
