#pragma once
#include <string>
#include "Vector2D.h"
/**
 * @brief List of sprites types available.
 */
typedef enum
{
  MOBJ_PLANT,	 // Map Object: plant.
  MOBJ_LIBRARY, // Map Object: library.
  NONE
} spriteType_t;

/**
 * @brief Struct that defines the data required to create
 *        a specific texture Sprite from a texture file.
 */
typedef struct
{
  /**
   * @brief Sprite type name/id.
   */
  spriteType_t sprite;
  /**
   * @brief  -x axis position index to get the texture.
   */
  int xPos;
  /**
   * @brief  -y axis position index to get the texture.
   */
  int yPos;
  /**
   * @brief  Sprite's amount of pixels height.
   */
  int height;
  /**
   * @brief  Sprite's amount of pixels width.
   */
  int width;
} spriteInfo_t;

extern spriteInfo_t spritesInfo[NONE];

/* ******************************************* */

/**
 * @brief List of available maps.
 */
typedef enum
{
  MAP_INDOOR,	 // Indoor house map.
  MAP_OUTDOOR, // Outdoor house map..
  MAP_NONE
} mapData_t;

/**
 * @brief Struct that defines the data required to create
 *        a specific map, with its texture and tile/map file.
 */
typedef struct
{
  /**
   * @brief Map enum.
   */
  mapData_t map;
  /**
   * @brief Map's Id.
   */
  std::string id;
  /**
   * @brief Path to the .map file.
   */
  std::string mapPath;
  /**
   * @brief Map's width tiles.
   */
  int width;
  /**
   * @brief Map's height tiles.
   */
  int height;
  /**
   * @brief Map's tile size (in px).
   */
  int tileSize;
  /**
   * @brief Player's initial position in the map.
   */
  Vector2D playerInitPosition;

} mapDataStruct_t;

extern mapDataStruct_t mapData[NONE];

/* ******************************************* */

/**
 * @brief List of available Triggers.
 */
typedef enum
{
  TRG_SHOW_DIALOGBOX,	      // Show GUI DialogBox.
  TRG_CLOSE_DIALOGBOX,      // Hide the GUI DialogBox
  TRG_CHANGEMAP_TO_INDOOR,  // Change to INDOOR house map.
  TRG_CHANGEMAP_TO_OUTDOOR, // Change to OUTDOOR map.
  TRG_NONE
} triggerEnum_t;

typedef void (*action_cb)();

/**
 * @brief Struct that defines Triggers and its
 *        a specific map, with its texture and tile/map file.
 */
typedef struct
{
  /**
   * @brief Trigger enum identifier.
   */
  triggerEnum_t triggerEnum;
  /**
   * @brief Trigger position in the map.
   */
  Vector2D position;
  /**
   * @brief Game texture scaling factor.
   */
  int scale;
  /**
   * @brief Callback function to execute when the trigger
   *        is activated.
   */
  action_cb action;
} triggersDefinition_t;

extern triggersDefinition_t triggersDefinitions[TRG_NONE];

/* ******************************************* */
