#include "Ground.h"

Ground::Ground(const Vector2& position)
	: DrawableActor("0")
{
	this->position = position;

	color = Color::Red;
}