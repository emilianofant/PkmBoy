#include "Map.h"
#include "Resources.h"
#include "../src/ECS/ECS.h"
#include "ECS/Components.h"

// @todo: move to global constant
int sc = 2;

void ShowDialogBox();
void ChangeMap_Indoor();

spriteInfo_t spritesInfo[NONE] = {
  { MOBJ_PLANT, 0, 2, 32, 16 },   // Plant sprite.
  { MOBJ_LIBRARY, 5, 0, 32, 16 }	// Library sprite.
};

mapDataStruct_t mapData[MAP_NONE] = {
  {MAP_INDOOR, "house", "assets/map/house.map", 22, 20, 8, Vector2D(256,256)},
  {MAP_OUTDOOR, "outdoor", "assets/map/outdoor.map", 28, 26, 16, Vector2D(288,320)}
};

triggersDefinition_t triggersDefinitions[TRIGGER_NONE] = {
  {TRG_SHOW_DIALOGBOX, Vector2D(288, 352), sc, ShowDialogBox},
  {TRG_CHANGE_MAP, Vector2D(288, 288), sc, ChangeMap_Indoor}
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
}

void ShowDialogBox()
{
  // @todo: toggle the active flag
}
