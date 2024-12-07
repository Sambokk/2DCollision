#pragma once
#include "Simplex2D.h"
#include "Vector3.h"
#include "Vector2.h"

Vector3 TripleProduct(Vector3 _v1, Vector3 _v2, Vector3 _v3);
Vector3 TripleProduct2(Vector3 _v1, Vector3 _v2, Vector3 _v3);


/*GJK알고리즘 계산에 사용되는 함수들*/
//
Vector3 SupportingPoint(Collider* c1, Collider* c2, Vector3 d);
Vector3 convexMaxPoint(vector<Vector2> s1, Vector2 d);
Vector3 circleMaxPoint(Vector2 pos, float r, Vector2 d);

bool NextSimplex2D(Simplex2D& points, Vector3& direction);
bool SameDirection(Vector3 _direction, Vector3 _ao);
bool GJKLine(Simplex2D& _points, Vector3& _direction);
bool GJKTriangle(Simplex2D& _points, Vector3& _direction);


//EPA알고리즘
//
Vector2 EPA(vector<Vector2>& polytope, Collider* shapeA, Collider* shapeB);