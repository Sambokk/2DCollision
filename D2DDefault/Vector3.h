#pragma once
#include "Vector2.h"


/// <summary>
/// 3Â÷¿ø ÁÂÇ¥
/// </summary>
struct Vector3
{
	float x;
	float y;
	float z;

public:
	Vector3()
		: x(0.f), y(0.f), z(0.f)
	{
	}

	Vector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Vector3(int _x, int _y, int _z)
		:x((float)_x), y((float)_y), z((float)_z)
	{
	}

	Vector3(Vector2 _v2)
		:x(_v2.x), y(_v2.y), z(0.f)
	{
	}

	//º¤ÅÍ ³¢¸®ÀÇ ¿¬»ê
	Vector3 operator + (Vector3 _otherV)
	{
		return Vector3(x + _otherV.x, y + _otherV.y, z + _otherV.z);
	}

	Vector3 operator - (Vector3 _otherV)
	{
		return Vector3(x - _otherV.x, y - _otherV.y, z - _otherV.z);
	}

	Vector3 operator * (int _i)
	{
		return Vector3(x * (float)_i, y * (float)_i, z * (float)_i);
	}

	Vector3 operator * (float _i)
	{
		return Vector3(x * _i, y * _i, z * _i);
	}

	Vector3 operator / (float _i)
	{
		return Vector3(x / _i, y / _i, z / _i);
	}

	//º¤ÅÍÀÇ Á¤±ÔÈ­
	Vector3 normalize()
	{
		float dist = (float)sqrt((float)pow(x, 2) + (float)pow(y, 2) + (float)pow(z,2));
		if (dist != 0)
		{
			*this = *this / dist;
			return *this;
		}
		return Vector3(0, 0, 0);
	}

};