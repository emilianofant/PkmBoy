#pragma once

#include "SDL_image.h"
#include "Game.h"

/**
 * @brief This class its in charge of reading, loading and drawing
 * texture in the game.
 */
class TextureManager
{
public:
	/**
	 * @brief Method to read a file path and then load a texture.
	 * 
	 * @param fileName  Path to the texture file.
	 * @return SDL_Texture* 
	 */
	static SDL_Texture* LoadTexture(const char* fileName);
	/**
	 * @brief This function is in charge of drawing and render textures
	 * into the game, and also manages some textures manipulation.
	 * 
	 * @param tex 
	 * @param src 
	 * @param dest 
	 * @param flip 
	 */
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};
