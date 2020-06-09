#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Resources.h"
#include "AssetManager.h"

#include <sstream>

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 160, 144};
AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, float scale = 1)
{
	_scale = scale;
	int flags = 0;
	_windowWidthRes = width*(int)_scale;
	_windowHeightRes = height*(int)_scale;

	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Substystem Initialised" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, _windowWidthRes, _windowHeightRes, flags);
		if(window)
		{
			std::cout << "window Created!" << _windowWidthRes << "x" << _windowHeightRes << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer) {
			SDL_SetRenderDrawColor(renderer, 15, 26, 15, 255);
			SDL_RenderSetScale(renderer, _scale, _scale);

			std::cout << "Render Created" << std::endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	// Adding texture to the "Texture library"
	// @todo: Move all texture library related to specific method
	assets->AddTexture("house", "assets/backgrounds/bkg_00.png");
	assets->AddTexture("outdoor", "assets/map/outdoor.png");
	assets->AddTexture("player", "assets/sprites/char_01.png");
	assets->AddTexture("map_objects", "assets/sprites/mobjs_00.png");

	// @todo: move SetMap to the constructor (?)
	map = new Map("outdoor", 2, 16);
	map->SetMap(MAP_OUTDOOR);

	// Player creation
	assets->CreatePlayer(Vector2D(288, 320), "player");
	assets->CreateTrigger(Vector2D(288, 288), _scale);
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& mapObjects(manager.getGroup(Game::groupMapObjects));
auto& triggers(manager.getGroup(Game::groupTriggers));

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	Entity* mainPlayer = players.at(0);

	SDL_Rect playersCol = mainPlayer->getComponent<ColliderComponent>().collider;
	Vector2D playerPos = mainPlayer->getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(cCol, playersCol))
		{
			mainPlayer->getComponent<TransformComponent>().resetDestinationPosition();
		}
	}

	for (auto& o : mapObjects)
	{
		SDL_Rect oCol = o->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(oCol, playersCol))
		{
			mainPlayer->getComponent<TransformComponent>().resetDestinationPosition();
		}
	}

	for (auto& t : triggers)
	{
		SDL_Rect oCol = t->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(oCol, playersCol))
		{
			for (auto& ti : tiles) {
				ti->destroy();
			}
			// Remove colliders from previous Map.
			for (auto& c : colliders) {
				if(c->getComponent<ColliderComponent>().tag == "wall") {
					c->destroy();
				}
			}
			map->~Map();
			// Remove Tiles entities
			
			// Change map
			map = new Map("house", 2, 8);
			map->SetMap(MAP_INDOOR);
			// Set player's position in the new map
			mainPlayer->getComponent<TransformComponent>().setNewPosition(Vector2D(128, 128));
			// Map objects creation
			assets->CreateMapObject(Vector2D(64,96), MOBJ_PLANT, _scale);
			assets->CreateMapObject(Vector2D(96,96), MOBJ_LIBRARY, _scale);
			// Destroy all Triggers
			t->destroy();
			break;
		}
	}

	camera.x = mainPlayer->getComponent<TransformComponent>().position.x - (_windowWidthRes / 4) + 16;
	camera.y = mainPlayer->getComponent<TransformComponent>().position.y - (_windowHeightRes / 4) + 16;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& o : mapObjects)
	{
		o->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleared" << std::endl;
}
