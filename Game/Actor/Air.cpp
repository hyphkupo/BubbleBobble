#include "Air.h"

Air::Air(const Vector2& position)
	: DrawableActor(" ")
{
	this->position = position;

	color = Color::White;
}