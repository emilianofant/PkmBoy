#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;
class Entity;
class Map;
class GUIManager;

/**
 * @brief Main class that defines the Game's Object.
 *
 */
class Game {
public:
	Game();
	~Game();

	/**
	 * @brief Flag that define if the Game is running or not.
	 */
	static bool isRunning;
	/**
	 * @brief The local reference for the SDL Renderer object. Will be
	 * 			  in charge of managing the Game's Render state.
	 */
	static SDL_Renderer *renderer;
	/**
	 * @brief The local reference to the SDL Event object, to manage
	 * 				the Game's events.
	 */
	static SDL_Event event;
	/**
	 * @brief Reference to an SDL Rectange that will be managing the
	 * 				Player's camera states.
	 */
	static SDL_Rect camera;
	/**
	 * @brief The local reference to the Game's Asset.
	 */
	static AssetManager* assets;
  /**
   * @brief Reference to the Game's map which will be rendered.
   */
  static Map* map;

  static Entity* player;
  static GUIManager* guiManager;
	/**
	 * @brief Enum list with all the available Group labels
	 * 				where the Entities can be organized and store with.
	 */
	enum groupLabels : std::size_t
	{
		groupMap, 			 // All Entities related to a Game's Map.
		groupPlayers,		 // All Players type of Entities.
		groupMapObjects, // All Map objects type of Entities.
		groupColliders,	 // All Map's Colliders tiles.
		groupTriggers,	 // All Triggers actionable Entities.
		groupGui,	 			 // All GUI (Graphic User Interface) Entities.
	};

  /**
   * @brief Enum of Control types.
   */
  typedef enum
  {
    CONTROL_PLAYER,	 // Control focus on Player.
    CONTROL_GUI,     // Control focus on GUI assets.
    CONTROL_NONE
  } controlType_t;

  static controlType_t _controlFocus;
  static bool processingTrigger;
	/**
	 * @brief Game's method to run when initiatiang.
	 *
	 * @param title 			Game's name;
	 * @param xpos 				-x axis position for the Game's windows.
	 * @param ypos 				-y axis position for the Game's windows.
	 * @param width 			Game's windows width size in pixels.
	 * @param height 			Game's windows heigh size in pixels.
	 * @param fullscreen  Flag to determine if Fullscreen mode or not.
	 * @param scale 			Integer to scale the window draw.
	 */
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, float scale);

	/**
	 * @brief Get if the Game is running or not.
	 *
	 * @return true
	 * @return false
	 */
	bool running() { return isRunning; }

	/**
	 * @brief Function that will be managing Events through the game.
	 */
	void handleEvents();

	/**
	 * @brief Method where all the Game's Objects/Entities and its Components
	 * 			  are going to be updated.
	 */
	void update();

	/**
	 * @brief Method where all the Game's Objects/Entities will be draw
	 * 				into the Game's window.
	 */
	void render();

	/**
	 * @brief Method to close the Game.
	 */
	void clean();

  static void saveScreenshot();


private:
	/**
	 * @brief The SDL Window's object from the SDL library to manage the Game's Window.
	 */
	SDL_Window *window;
	/**
	 * @brief Width resolution for the Game's window.
	 */
	int _windowWidthRes;
	/**
	 * @brief Height resolution for the Game's window.
	 */
	int _windowHeightRes;
	/**
	 * @brief The local reference to a game Rendere
	 * 				scaling factor.
	 */
	float _scale = 1;
};
