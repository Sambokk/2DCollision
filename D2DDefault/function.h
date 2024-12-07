#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Simplex2D.h"

class Collider;

//2Â÷¿ø º¤ÅÍ
float Dot(Vector2 _v1, Vector2 _v2);
float SignedDot(Vector2 _v1, Vector2 _v2);
float Distance(Vector2 _v1, Vector2 _v2);
Vector2 RotateVertex(Vector2 v, float radian);

//2Â÷¿ø º¤ÅÍ -> d2d1ÁÂÇ¥



//3Â÷¿ø º¤ÅÍ
float SignedDot(Vector3 _v1, Vector3 _v2);
Vector3 Cross(Vector3 _v1, Vector3 _v2);


template<typename T>
void safeDeleteVector(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] != nullptr)
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
void safeDeleteMap(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); iter++)
	{
		if (iter->second != nullptr)
			delete iter->second;
	}
	_map.clear();
}