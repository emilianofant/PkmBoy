#pragma once

#include "ECS.h"
#include "AssetManager.h"
#include "Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class GUILabel : public Component
{
public:
	GUILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) :
		labelText(text), labelFont(font), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;

		SetDialogBoxText(labelText, labelFont);
	}

	~GUILabel()
	{}

	void SetDialogBoxText(std::string text, std::string font)
	{
    // todo: check space between line
		SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(Game::assets->GetFont(font), text.c_str(), textColour, 16 * _MAX_CHARS_PER_LINE);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
  const int _MAX_CHARS_PER_LINE = 18;
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};
