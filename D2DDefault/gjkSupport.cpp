#pragma once
#include "pch.h"
#include "define.h"
#include "function.h"
#include "gjkSupport.h"
#include "Collider.h"

/// <summary>
/// a x b x c의 삼중곱
/// </summary>
Vector3 TripleProduct(Vector3 _a, Vector3 _b, Vector3 _c)
{
	Vector3 a = _a;
	Vector3 b = _b;
	Vector3 c = _c;

	Vector3 first = Cross(a, b);
	Vector3 second = Cross(first, c);

	return Vector3(second);
}


/// <summary>
/// a x (b x c)의 삼중곱
/// </summary>
Vector3 TripleProduct2(Vector3 _a, Vector3 _b, Vector3 _c)
{
	Vector3 a = _a;
	Vector3 b = _b;
	Vector3 c = _c;

	Vector3 first = Cross(b, c);
	Vector3 second = Cross(a, first);

	return Vector3(second);
}


/// <summary>
/// Convex형태의 d방향으로 가장 멀리 있는 점
/// </summary>
Vector3 convexMaxPoint(vector<Vector2> s1, Vector2 d)
{
	Vector2 maxPoint;
	float maxDistance = numeric_limits<float>::lowest();
	for (Vector2 vertex : s1)
	{
		float distance = SignedDot(vertex, d);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = vertex;
		}
	}
	return maxPoint;
}


/// <summary>
///Circle형태의 d방향으로 가장 멀리 있는 점
/// </summary>
Vector3 circleMaxPoint(Vector2 pos, float r, Vector2 d)
{
	return pos + d.normalize() * r;
}

/// <summary>
/// 민코스키 차로 구해지는 두 도형 D방향으로의 최대 거리
/// </summary>
Vector3 SupportingPoint(Collider* c1, Collider* c2, Vector3 d)
{
	Vector3 maxPoint1, maxPoint2;

	if (c1->getType() == COLLIDER_TYPE::CIRCLE)
		maxPoint1 = circleMaxPoint(c1->getPosition(), c1->getRadius(), Vector2(d.x, d.y).normalize());
	else
		maxPoint1 = convexMaxPoint(c1->getVertexs(), Vector2(d.x, d.y).normalize());

	if (c2->getType() == COLLIDER_TYPE::CIRCLE)
		maxPoint2 = circleMaxPoint(c2->getPosition(), c2->getRadius(), Vector2(d.x, d.y).normalize() * -1);
	else
		maxPoint2 = convexMaxPoint(c2->getVertexs(), (Vector2(d.x, d.y).normalize()) * -1);


	return maxPoint1 - maxPoint2;
}

/// <summary>
/// 
/// </summary>
bool NextSimplex2D(Simplex2D& _points, Vector3& _direction)
{
	switch (_points.size())
	{
	case 2:		return GJKLine(_points, _direction);
	case 3:		return GJKTriangle(_points, _direction);
	}

	return false; //이까지 오면 안됨
}


/// <summary>
/// 두개의 벡터가 같은 방향에 있는가?
/// </summary>
bool SameDirection(Vector3 _direction, Vector3 _ao)
{
	return SignedDot(_direction, _ao) > 0;
}


/// <summary>
/// Simplex의 점들 중 2개를 찾았을 때
/// </summary>
bool GJKLine(Simplex2D& _points, Vector3& _direction)
{
	Vector3 a = _points[0];
	Vector3 b = _points[1];

	Vector3 ab = b - a;
	Vector3 ao = a * -1;

	if (SameDirection(ab, ao))
	{
		_direction = TripleProduct(ab, ao, ab).normalize();
		//return true; 
	}
	else
	{
		_points = { a };
		_direction = ao;
	}
	return false;
}


/// <summary>
/// Simplex의 점 3개로 원점을 포함하는지 판단
/// </summary>
bool GJKTriangle(Simplex2D& _points, Vector3& _direction)
{
	Vector3 a = _points[0];
	Vector3 b = _points[1];
	Vector3 c = _points[2];

	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ao = a * -1;

	Vector3 abc = Cross(ab, ac);

	Vector3 r = TripleProduct(ab, ac, ac);

	if (SameDirection(TripleProduct(ab, ac, ac), ao))
	{
		if (SameDirection(ac, ao))
		{
			_points = { a,c };
			_direction = TripleProduct(ac, ao, ac).normalize();
		}
		else
		{
			return GJKLine(_points = { a,b }, _direction);
		}
	}
	else
	{
		if (SameDirection(TripleProduct2(ab, ab, ac), ao))
		{
			return GJKLine(_points = { a,b }, _direction);
		}
		else
		{
			return true;
		}
	}
	return false;
}


/// <summary>
/// 침투점 계산
/// </summary>
Vector2 EPA(vector<Vector2>& polytope, Collider* shapeA, Collider* shapeB)
{
	int minIndex = 0;
	float minDistance = std::numeric_limits<float>::infinity();
	Vector2 minNormal;

	while (minDistance == std::numeric_limits<float>::infinity())
	{
		for (size_t i = 0; i < polytope.size(); i++)
		{
			size_t j = (i + 1) % polytope.size();

			Vector2 vertexI = polytope[i];
			Vector2 vertexJ = polytope[j];

			Vector2 ij = vertexJ - vertexI;

			Vector2 normal = Vector2(ij.y, -ij.x).normalize();
			float distance = SignedDot(normal, vertexI);

			if (distance < 0)
			{
				distance *= -1;
				normal = normal * -1;
			}

			if (distance < minDistance)
			{
				minDistance = distance;
				minNormal = normal;
				minIndex = j;
			}
		}

		Vector3 support3 = SupportingPoint(shapeA, shapeB, minNormal);
		Vector2 support = Vector2(support3.x, support3.y);
		float sDistance = SignedDot(minNormal, support);

		if (abs(sDistance - minDistance) > 0.001)
		{
			minDistance = std::numeric_limits<float>::infinity();
			polytope.insert(polytope.begin() + minIndex, support);
			//minIndex위치에 support를 추가한다. 
		}
	}

	return minNormal * (minDistance + (float)0.001);
}

