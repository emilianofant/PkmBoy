#pragma once
#include "SDL.h"
#include "Animation.h"
#include "Game.h"
#include <map>
#include "AssetManager.h"

/**
 * @brief Component that will define Sprite management and its behaviors.
 */
class SpriteComponent : public Component
{
private:
    /**
   * @brief Local reference to the Entity's TransformComponent.
   */
  TransformComponent *transform;
  /**
   * @brief Local reference to the Game's Texture manager.
   */
  SDL_Texture *texture;
  /**
   * @brief Reference to the  SDL Source Rectangle 
   */
  SDL_Rect srcRect;
  /**
   * @brief Reference to the SDL Source Rectangle 
   */
  SDL_Rect destRect;
  /**
   * @brief Flag that defines is the Sprite is animated or not. 
   */
  bool animated = false;
  bool mapObject = false;
  /**
   * @brief Amount of frames that the Sprite's animation contains.
   *        Default: one frame.
   */
  int frames = 1;
  /**
   * @brief Amount of milliseconds that an Animation will be set.
   */
  int speed = 250;

public:
  /**
   * @brief Reference to the -x frame position in case of animated sprite.
   */
  int animIndex = 0;
  /**
   * @brief Map where to store available animations. 
   */
  std::map<const char*, Animation> animations;
  /**
   * @brief Reference to an SDL Flip state in order to invert an image
   *        horizontally or not. 
   */
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  /**
   * @brief Construct a new Sprite Component object
   */
  SpriteComponent() = default;

  /**
   * @brief Construct a new Sprite Component object with animated sprite.
   * 
   * @param id          String identifier.
   * @param isAnimated  Flag to set animated value to sprite.
   */
  SpriteComponent(std::string id, bool isAnimated)
  {
    if (isAnimated) {
      animated = isAnimated;

      Animation front_idle = Animation(0, 1, 400);
      Animation front_walk = Animation(0, 2, 400);
      Animation back_idle = Animation(2, 1, 400);
      Animation back_walk = Animation(2, 2, 400);
      Animation side_idle = Animation(1, 1, 400);
      Animation side_walk = Animation(1, 2, 400);

      animations.emplace("player_front_idle", front_idle);
      animations.emplace("player_front_walk", front_walk);
      animations.emplace("player_back_idle", back_idle);
      animations.emplace("player_back_walk", back_walk);
      animations.emplace("player_side_idle", side_idle);
      animations.emplace("player_side_walk", side_walk);

      Play("player_front_idle");
    } 
    
    setTex(id);
  }
  
  /**
   * @brief Construct a new Sprite Component object for a Map's object.
   * 
   * @param id         Texture id from which to get the texture.
   * @param srcX       -x axis coordinate to get the texture.
   * @param srcY       -y axis coordinate to get the texture.
   * @param sprWidth   Sprite's texture amount of pixels width.
   * @param sprHeight  Sprite's texture amount of pixels height.
   */
  SpriteComponent(std::string id, int srcX, int srcY, int sprWidth, int sprHeight)
  {
    mapObject = true;

    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = sprWidth;
    srcRect.h = sprHeight;
    
    setTex(id);
  }

  /**
   * @brief Destroy the Sprite Component object
   */
  ~SpriteComponent()
  {}

  /**
   * @brief Set the Tex object.
   * 
   * @param id String texture identifier. 
   */
  void setTex(std::string id)
  {
    texture = Game::assets->GetTexture(id);
  }

  /**
   * @brief Initialize rectangles.
   */
  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();

    if(!mapObject) {
      srcRect.x = srcRect.y = 0;
    }

    srcRect.w = transform->width;
    srcRect.h = transform->height;
  }

  void update() override
  {
    if(animated)
    {
      srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
      srcRect.y = animIndex * transform->height;
    }
    
    destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
    destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
  }

  void draw() override
  {
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
  }

  void Play(const char* animName)
  {
    frames = animations[animName].frames;
    animIndex = animations[animName].index;
    speed = animations[animName].speed;
  }
};
