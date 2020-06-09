#pragma once
#include <string>

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
} mapDataStruct_t;

extern mapDataStruct_t mapData[NONE];