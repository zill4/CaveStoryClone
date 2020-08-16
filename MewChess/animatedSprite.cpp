/*
	animates our sprites
*/
#include "animatedSprite.h"
#include "graphics.h"
#include "sprite.h"

AnimatedSprite::AnimatedSprite() {}


AnimatedSprite::AnimatedSprite(Graphics& graphics, const std::string& filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate) : 
	Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	_frameIndex(0),
	_timeToUpdate(timeToUpdate),
	_visible(true),
	_currentAnimationOnce(false),
	_currentAnimation(""),
	_timeElapsed(0)
{} 

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
	std::vector<SDL_Rect> rectangles;
	for (int sprite = 0; sprite < frames; sprite++)
	{
		SDL_Rect newRect = { (sprite + x) * width, y, width, height };
		rectangles.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations()
{
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
	this->_currentAnimation = once;
	if (this->_currentAnimation != animation)
	{
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible)
{
	this->_visible = visible;
}

void AnimatedSprite::stopAnimation()
{
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
	Sprite::update();

	// Happening every frame
	this->_timeElapsed += elapsedTime;
	// Checking when to go to the next frame in the animation.
	if (this->_timeElapsed > this->_timeToUpdate)
	{
		// If we are not at the last frame, increase to next frame
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1)
			this->_frameIndex++;
		else
		{
			//Else go back to the first frame
			if (this->_currentAnimationOnce == true)
				this->setVisible(false);
			this->_frameIndex = 0;
			this->animationDone(this->_currentAnimation);
		}
	}
}

void AnimatedSprite::draw(Graphics& graphics, int x, int y)
{
	SDL_Rect destinationRectangle;
	destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
	destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
	// May need accessor for the source rectangle
	destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
	destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

	SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
	// Also not accessible
	graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
}

void AnimatedSprite::animationDone(std::string currentAnimation)
{

}

void AnimatedSprite::setupAnimations()
{
	// Running left animation, height width, with no offset.
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0,0));
}