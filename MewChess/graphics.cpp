/*
	Graphics Class
	Holds all information dealing with graphics for the game.
*/
#include "graphics.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Cavestory");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);

}

SDL_Surface* Graphics::loadImage(const std::string& filePath)
{
	// If its 0, then it hasn't been loaded yet.
	if (this->_spriteSheets.count(filePath) == 0)
	{
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
	// Copies to renderer texture part of the rect we copy, and the destination.
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
	return (this->_renderer);
}