#pragma once
#include "SDL.h"

/**
 * @brief This component define the Tiles and its texture
 * management: getting the textures from TextureManager and
 * then draw/update them in the Game.
 */
class TileComponent : public Component
{
public:
  /**
   * @brief Local reference to a SDL Texture instance.
   */
  SDL_Texture* texture;
  /**
   * @brief Local reference to the Game's SDL Rectangules instance.
   */
  SDL_Rect srcRect, destRect;
  /**
   * @brief Position data for the Component.
   */
  Vector2D position;

  /**
   * @brief Construct a new Tile Component object
   */
  TileComponent() = default;

  /**
   * @brief Destroy the Tile Component object
   * @todo: Performance issue if we are not managing the textures.
   *        This could be moved the Texture manager.
   */
  ~TileComponent()
  {
    // SDL_DestroyTexture(texture);
  }
  /**
   * @brief Construct a new Tile Component object
   *
   * @param srcX    -x axis coordinate from where to the sprite tile start.
   * @param srcY    -y axis coordinate from where to the sprite tile start.
   * @param xpos    -x axis coordinate where the tile will be placed.
   * @param ypos    -y axis coordinate where the tile will be placed.
   * @param tsize   Tile size in pixels.
   * @param tscale  Tile scaling factor.
   * @param id      Tile identifier.
   */
  TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
  {
    texture = Game::assets->GetTexture(id);

    position.x = xpos;
    position.y = ypos;

    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = srcRect.h = tsize;

    destRect.w = destRect.h = tsize * tscale;
  }

  void update() override
  {
    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;
  }

  void draw() override
  {
    TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
  }
};
