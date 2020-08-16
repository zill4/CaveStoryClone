/*
	AnimatedSprite Class
	Holds logic for animating sprites/
*/

#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H
#include "sprite.h"
#include "globals.h"
#include <map>
#include <vector>
#include <string>

class Graphics;


class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);

	// once optional paramater

	void playAnimation(std::string animation, bool once = false);
	
	// updates the animated sprite (timer)
	void update(int elapsedTime);

	// Draws sprite to the screen
	void draw(Graphics& graphics, int x, int y);

	// sets up all animations for a sprite
	virtual void setupAnimations();

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	// Adds an animation to the map of animations for the sprite
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	// resets all animations associated with the sprite
	void resetAnimations();

	// stops current animation
	void stopAnimation();

	// change visiblitly of animated sprite
	void setVisible(bool visible);

	// happens everytime an animation ends
	virtual void animationDone(std::string currentAnimation);
private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	// if in sprite sheet not exactly 16 pixels
	std::map<std::string, Vector2> _offsets;

	// Which frame in animation
	int _frameIndex;
	// Time elapsed where we are at
	double _timeElapsed = 0;
	// If animation is visible.
	bool _visible;

};
#endif