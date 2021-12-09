#include "sprite_animation.hpp"

SpriteAnimation::SpriteAnimation(const string& ID)
	:
	_ID(ID)
{

}

const string& SpriteAnimation::getID() const
{
	return _ID;
}