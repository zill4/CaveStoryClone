/*
	Game Class
	This class holds all information for our main game loop
*/

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() 
{
	// Initializes game sub systems
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() 
{

}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;

	// Gets number of seconds since SDL init
	int LAST_UPDATE_TIME = SDL_GetTicks();
	// Start game loop
	while (true) 
	{
		// Resets checking for input each frame
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) 
		{
			// Checking keys
			if (event.type == SDL_KEYDOWN) 
			{
				if (event.key.repeat == 0) 
				{
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) 
			{
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) 
			{
				return;
			}
		}
		// Also if === true
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) 
		{
			return;
		}
		// This returns the elapsed time taken betwen last getTicks and this getTicks
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;
	}
}

void Game::draw(Graphics& graphics)
{

}

void Game::update(float elapsedTime)
{

}