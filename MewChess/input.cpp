#include "input.h"

/*
	Input Class
	Keeps track of keyboard state (or any input)
*/

// This function gets called at the beginning of each new frame to reset the keys that are no longer relevant.
void Input::beginNewFrame() {
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

// Called when key is pressed down
void Input::keyDownEvent(const SDL_Event& event) {
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldkeys[event.key.keysym.scancode] = true;
}
// Called when key is lifted
void Input::keyUpEvent(const SDL_Event& event) {
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldkeys[event.key.keysym.scancode] = false;
}

// check if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
	return (this->_pressedKeys[key]);
}

// check if a cerntain key is currently being held
bool Input::wasKeyReleased(SDL_Scancode key)
{
	return (this->_releasedKeys[key]);
}