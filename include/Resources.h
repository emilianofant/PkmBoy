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
