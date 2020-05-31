#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "../src/ECS/ECS.h"
#include "SDL2/SDL_ttf.h"
#include "Resources.h"

/**
 * @brief This class is in charge of managing different types of
 *        assets: creation, manipulation, define textures and components
 *        that are going to be part of any entity.
 */
class AssetManager
{
public:

    /**
   * @brief Construct a new Asset Manager object.
   * 
   * @param man  Game's Manager reference.
   */
  AssetManager(Manager* man);
  
  /**
   * @brief Destroy the Asset Manager object
   */
  ~AssetManager();

  // ************
  // GameObjects
  // ************
  /**
   * @brief Create a Player object.
   * 
   * @param pos  Vector with the initial Player's position.
   * @param id   String name to tag the Asset. 
   */
  void CreatePlayer(Vector2D pos, std::string id);
  
  /**
   * @brief Create a Map object.
   * 
   * @param pos  Vector with the Object's position.
   * @param spr  Sprite type id. 
   * @param sc   Texture scaling factor. 
   */
  void CreateMapObject(Vector2D pos, spriteType_t spr, int sc);

  // ************
  // Texture Management
  // ************
  /**
   * @brief This method adds and stores a Texture to the Game to 
   *        be accesible when needed.
   * 
   * @param id    Texture's string identifier.
   * @param path  Local path to the texture's file.
   */
  void AddTexture(std::string id, const char* path);
  
  /**
   * @brief Get the Texture object from the store.
   * 
   * @param id  Texture's identifier. 
   * 
   * @return SDL_Texture* 
   */
  SDL_Texture * GetTexture(std::string id);

private:
  /**
   * @brief Local reference to the Game's Manager instance.
   */
  Manager* manager;
  /**
   * @brief Map to store Textures with its identifier. 
   */
  std::map<std::string, SDL_Texture*> textures;
};