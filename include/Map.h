#pragma once
#include <string>

/**
 * @brief This class is responsible for reading a .map file, which contains a 
 *        matrix of values that are indexes of tiles in a .png file from which the
 *        program will get the textures.
 */
class Map
{
public:
    /**
     * @brief   Construct a new Map object
     * 
     * @param tID   Texture id.
     * @param ms    Map texture scaling factor.
     * @param ts    Actual tile size. (In this programs are 8px x 8px)
     */
    Map(std::string tID, int ms, int ts);
    
    /**
     * @brief Destroy the Map object
     */
    ~Map();

    /**
     * @brief   This function is in charge of create/add a TileComponent
     *          to the manager, with its position, size and id;
     * 
     * @param srcX  Position in -x axis where the texture starts in the texture file.
     * @param srcY  Position in -y axis where the texture starts in the texture file.
     * @param xpos  Position in -x axis where the tile will be placed in the screen.
     * @param ypos  Position in -y axis where the tile will be placed in the screen.
     */
	void AddTile(int srcX, int srcY, int xpos, int ypos);
    /**
     * @brief Method to read a txt file, which describes the map's tiles composition
     *        and also the map's "walkable area" limits.
     * 
     * @param path  The map's txt file path.
     * @param sizeX The map's x size / amount of tiles column.
     * @param sizeY The map's y size / amount of tiles rows.
     */
    void LoadMap(std::string path, int sizeX, int sizeY);

private:
    /**
     * @brief Local reference to the Map's Texture id from where to get
     *        the textures to use.
     */
    std::string texID;
    /**
     * @brief Integer to define a map scaling factor.
     */
    int mapScale;
    /**
     * @brief Map's Tiles size.
     */
    int tileSize;
    /**
     * @brief  Factor to scale textures.
     */
    int scaledSize;
};
