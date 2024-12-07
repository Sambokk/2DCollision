#pragma once
#include "pch.h"

/// <summary>
/// 2차원 좌표
/// </summary>
struct Vector2
{
	float x;
	float y;

public:
	Vector2()
		: x(0.f)
		, y(0.f)
	{
	}

	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	Vector2(int _x, int _y)
		:x((float)_x)
		, y((float)_y)
	{
	}

	//포인터 구조체를 받기 위한
	Vector2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vector2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{
	}

	Vector2 operator -()
	{
		return Vector2(-x, -y);
	}


	//벡터 끼리의 연산
	Vector2 operator + (Vector2 _otherV)
	{
		return Vector2(x + _otherV.x, y + _otherV.y);
	}

	Vector2 operator - (Vector2 _otherV)
	{
		return Vector2(x - _otherV.x, y - _otherV.y);
	}

	Vector2& operator += (Vector2 _otherV)
	{
		x += _otherV.x;	y += _otherV.y;
		return *this;
	}

	Vector2& operator -= (Vector2 _otherV)
	{
		x -= _otherV.x;	y -= _otherV.y;
		return *this;
	}

	Vector2 operator * (int _i)
	{
		return Vector2(x * (float)_i, y * (float)_i);
	}

	Vector2 operator * (float _i)
	{
		return Vector2(x * _i, y * _i);
	}

	Vector2 operator / (float _i)
	{
		return Vector2(x / _i, y / _i);
	}

	Vector2& operator *= (float _i)
	{
		x *= _i;	y *= _i;
		return *this;
	}

	Vector2& operator *= (int _i)
	{
		x *= (float)_i;	y *= (float)_i;
		return *this;
	}

	Vector2& operator += (float _i)
	{
		x += _i;	y += _i;
		return *this;
	}

	Vector2& operator += (int _i)
	{
		x += (float)_i;	y += (float)_i;
		return *this;
	}

	Vector2& operator -= (float _i)
	{
		x -= _i;	y -= _i;
		return *this;
	}

	Vector2& operator -= (int _i)
	{
		x -= (float)_i;	y -= (float)_i;
		return *this;
	}


	//벡터의 정규화
	Vector2 normalize()
	{
		float dist = (float)sqrt((float)pow(x, 2) + (float)pow(y, 2));
		if (dist != 0)
		{
			*this = *this / dist;
			return *this;
		}
		return Vector2(0, 0);
	}
	//사용 : vec.normalize();
};