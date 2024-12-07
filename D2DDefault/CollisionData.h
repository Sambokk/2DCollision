#pragma once
#include "Vector2.h"

struct CollisionData
{
	bool isCollision;
	Vector2 depth;

public:
	CollisionData()
		:isCollision(false), depth(0, 0)
	{}

	CollisionData(bool _is, Vector2 _depth)
		:isCollision(_is), depth(_depth)
	{}

	CollisionData(Vector2 _depth)
		:isCollision(true), depth(_depth)
	{}

	CollisionData(bool _is)
		:isCollision(false), depth(0, 0)
	{}

	CollisionData filp()
	{
		depth *= -1;
		return *this;
	}
};