#pragma once
#include "Vector2.h"

class Rigidbody;

struct RigidbodyData
{
	Rigidbody* r1;
	Rigidbody* r2;
	Vector2 depth;

	RigidbodyData(Rigidbody* _r1, Rigidbody* _r2, Vector2 _d)
	{
		r1 = _r1;
		r2 = _r2;
		depth = _d;
	}

};