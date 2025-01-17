#include "Wall.h"

Wall::Wall(const Vector2& position)
	: DrawableActor("1")
{
	this->position = position;

	color = Color::Blue;
}