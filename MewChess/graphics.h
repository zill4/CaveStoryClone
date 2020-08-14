#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

struct SDL_Window;
struct SDL_Renderer;

class Graphics 
{

public: 
	Graphics();
	~Graphics();

	// Loads an image into the _sprteSheets map if it desont already exist
	// As a result, each image will only ever be loaded once
	// Returns teh image from the map regardless of whether or not it was just loaded
	SDL_Surface* loadImage(const std::string &filePath);

	// Void blitSurface
	// Draws  a texture to a certain part of the screen
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	// void flip
	// Renders everything to the screen
	void flip();

	// void clear
	// Clears the screen
	void clear();

	// Returns the renderer
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;
};
#endif // !GRAPHICS_H
