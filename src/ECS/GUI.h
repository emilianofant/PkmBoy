#pragma once

#include "ECS.h"
#include "Game.h"
#include "TextureManager.h"

#include <SDL2/SDL.h>
#include <string>

/**
 * @brief This Component is in charge of the definition of different
 *        GUI elements, their behaviour and textures.
 */
class GUI : public Component
{
public:
  /**
   * @brief Enum of GUI types available to create.
   */
  typedef enum
  {
    GUI_DIALOG_BOX,
    GUI_MENU
  } guiComponentEnum_t;

  /**
   * @brief Construct a new GUI object
   *
   * @param sc  Texture scaling factor
   */
	GUI(int sc)
	{
    _scale = sc;
  }

  /**
   * @brief Destroy the GUI object and its texture.
   */
  ~GUI()
	{
    SDL_DestroyTexture(_texture);
  }

  /**
   * @brief Create a Dialog Box type object.
   */
	void CreateDialogBox()
	{
    _guiType = GUI_DIALOG_BOX;
    // @todo: create a 'gui.png' with textures to use here.
    _texture = Game::assets->GetTexture("gui_dialogBox");

    _srcRect.x = 0;
    _srcRect.y = 0;
    _srcRect.w = 160;
    _srcRect.h = 48;

    _destRect.x = 0;
    _destRect.y = 96 * _scale;
    _destRect.w = 160 * _scale;
    _destRect.h = 48 * _scale;
	}

  /**
   * @brief Function to Show the GUI Component.
   */
  void Show()
  {
    _isActive = true;
  }

  /**
   * @brief Function to hide the GUI Component.
   */
  void Hide()
  {
    _isActive = false;
  }

  void init() override
  {
    _isActive = false;
  }

	void draw() override
	{
    if(_isActive) {
      TextureManager::Draw(_texture, _srcRect, _destRect, SDL_FLIP_NONE);
    }
	}

private:
  /**
   * @brief The local reference to the texture scaling factor.
   */
  int _scale;
  /**
   * @brief The local reference for the GUI type define when
   *        creating the Component.
   */
  guiComponentEnum_t _guiType;
  /**
     * @brief Local reference to a SDL Texture instance.
     */
  SDL_Texture* _texture;
  /**
   * @brief Local reference to the Component's SDL Rectangules
   *        to draw.
   */
  SDL_Rect _srcRect, _destRect;
  /**
   * @brief Flag to determine if the element is Active or not, and
   *        draw/update it depending on that.
   */
  bool _isActive;
};
