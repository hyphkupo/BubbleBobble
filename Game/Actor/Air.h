#pragma once

#include <Actor/DrawableActor.h>

class Air : public DrawableActor
{
	RTTI_DECLARATIONS(Air, DrawableActor)

public:
	Air(const Vector2& position);
};