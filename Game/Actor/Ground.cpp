#include "Ground.h"

Ground::Ground(const Vector2& position)
	: DrawableActor("`")
{
	this->position = position;

	color = Color::Purple;
}