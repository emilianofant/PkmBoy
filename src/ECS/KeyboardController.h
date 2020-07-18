#pragma once

#include "Resources.h"
#include "GUIManager.h"

/**
 * @brief Defines a Component that will manage Keyboard events.
 */
class KeyboardController : public Component
{
public:
  /**
   * @brief The local reference to the Entity's TransformComponent.
   */
  TransformComponent *transform;
  /**
   * @brief The local reference to the Entity's SpriteComponent.
   */
  SpriteComponent *sprite;

  bool _isActive = false;

  void setActiveController()
  {
    _isActive = true;
  }

  void setInactiveController()
  {
    _isActive = false;
  }
  /**
   * @brief Init function to set the references to the Entity's
   *        Transform and Sprite Components.
   */
  void init() override
  {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
  }

  void update() override
  {
    // Shorcut: if the CONTROL focus is not in the entity that contains
    // this component, then return.
    if (!_isActive) { return; }


    /*
     *  Player Focus Controller
     */
    // @todo: move the sprite play to a manager where the animation
    // should be able to get states in order to keep the animation
    // goint when still moving.
    if(Game::event.type == SDL_KEYDOWN && Game::_controlFocus == Game::CONTROL_PLAYER)
    {
      switch (Game::event.key.keysym.sym)
      {
        case SDLK_UP:
          transform->fixedMovement("DIR_UP");
          sprite->Play("player_back_walk");
          break;
        case SDLK_LEFT:
          transform->fixedMovement("DIR_LEFT");
          sprite->Play("player_side_walk");
          break;
        case SDLK_RIGHT:
          transform->fixedMovement("DIR_RIGHT");
          sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
          sprite->Play("player_side_walk");
          break;
        case SDLK_DOWN:
          transform->fixedMovement("DIR_DOWN");
          sprite->Play("player_front_walk");
          break;
        default:
          break;
      }
    }

    if(Game::event.type == SDL_KEYUP && Game::_controlFocus == Game::CONTROL_PLAYER)
    {
      switch (Game::event.key.keysym.sym)
      {
        case SDLK_UP:
          sprite->Play("player_back_idle");
          break;
        case SDLK_LEFT:
          sprite->Play("player_side_idle");
          sprite->spriteFlip = SDL_FLIP_NONE;
          break;
        case SDLK_RIGHT:
          sprite->Play("player_side_idle");
          break;
        case SDLK_DOWN:
          sprite->Play("player_front_idle");
          break;
        case SDLK_ESCAPE:
          Game::isRunning = false;
        default:
          break;
      }
    }

    /*
     *  GUI Focus Controller
     */
    if(Game::event.type == SDL_KEYDOWN && Game::_controlFocus == Game::CONTROL_GUI)
    {
      switch (Game::event.key.keysym.sym)
      {
        case SDLK_a:
          Game::guiManager->CloseDialogBox();
          break;
        case SDLK_DOWN:
          break;
        default:
          break;
      }
    }
    
    if(Game::event.type == SDL_KEYUP)
    {
      switch (Game::event.key.keysym.sym)
      {
        case SDLK_F12:
          Game::saveScreenshot();
          break;
        default:
          break;
      }
    }
  }
};
