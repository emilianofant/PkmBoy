#include "Resources.h"

spriteInfo_t spritesInfo[NONE] = {
    { MOBJ_PLANT, 0, 2, 32, 16 },   // Plant sprite.	
    { MOBJ_LIBRARY, 5, 0, 32, 16 }	// Library sprite.
};

mapDataStruct_t mapData[MAP_NONE] = {
    {MAP_INDOOR, "house", "assets/indoor/house.map", 22, 20},
    {MAP_OUTDOOR, "outdoor", "assets/map/outdoor.map", 28, 26}
};
