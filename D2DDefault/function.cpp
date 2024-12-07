#pragma once
#include "pch.h"
#include "define.h"
#include "function.h"
#include "Collider.h"

float Dot(Vector2 _v1, Vector2 _v2)
{
	return abs(_v1.x * _v2.x + _v1.y * _v2.y);
}

float SignedDot(Vector3 _v1, Vector3 _v2)
{
	return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
}

float SignedDot(Vector2 _v1, Vector2 _v2)
{
	return _v1.x * _v2.x + _v1.y * _v2.y;
}

Vector3 Cross(Vector3 _v1, Vector3 _v2)
{
	return Vector3(
		_v1.y * _v2.z - _v1.z * _v2.y,
		_v1.z * _v2.x - _v1.x * _v2.z,
		_v1.x * _v2.y - _v1.y * _v2.x);
}

float Distance(Vector2 _v1, Vector2 _v2)
{
	return (float)sqrt(
		(float)pow(_v1.x - _v2.x, 2) + (float)pow(_v1.y - _v2.y, 2));
}

Vector2 RotateVertex(Vector2 v, float radian)
{
	Vector2 origin = v;
	v.x = origin.x * cos(-radian) - origin.y * sin(-radian);
	v.y = origin.x * sin(-radian) + origin.y * cos(-radian);

	return v;
}