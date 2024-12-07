#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "Vector2.h"

UINT Collider::idIndex = 0;

Collider::Collider(Object* _owner, float _radius)
	:id(0), owner(nullptr), collisionCount(0), position{}
	, type(COLLIDER_TYPE::DEFAULT), radius(0)
	,rotation(0)
{
	id = idIndex++;
	owner = _owner;
	type = COLLIDER_TYPE::CIRCLE;
	radius = _radius;
}

Collider::Collider(Object* _owner, float _halfWidth, float _halfHeight, float _rotation)
	:id(0), owner(nullptr), collisionCount(0), position{}
	, type(COLLIDER_TYPE::DEFAULT), radius(0)
	, rotation(0)
	,vertexs{}
{
	id = idIndex++;
	owner = _owner;
	type = COLLIDER_TYPE::CONVEX;

	vertexs.push_back(Vector2(- _halfWidth,  - _halfHeight));
	vertexs.push_back(Vector2(  _halfWidth,  - _halfHeight));
	vertexs.push_back(Vector2(  _halfWidth,    _halfHeight));
	vertexs.push_back(Vector2(- _halfHeight,   _halfHeight));
	rotation = _rotation;
}

Collider::Collider(Object* _owner, vector<Vector2> _vertexs, float _rotation)
	:id(0), owner(nullptr), collisionCount(0), position{}
	, type(COLLIDER_TYPE::DEFAULT), radius(0)
	, rotation(0), vertexs{}
{
	id = idIndex++;
	owner = _owner;
	type = COLLIDER_TYPE::CONVEX;

	vertexs = _vertexs;
	rotation = _rotation;
}

Collider::~Collider()
{
}

void Collider::update()
{
	position = owner->getPosition();
	rotation = owner->getRotation();
	vertexs = owner->getVertexs();
}

void Collider::OnCollisionEnter(Collider* _other, Vector2 _depth)
{
	owner->OnCollisionEnter(_other->getOwner(), _depth);
	collisionCount++;
}

void Collider::OnCollision(Collider* _other, Vector2 _depth)
{
	owner->OnCollision(_other->getOwner(), _depth);
}

void Collider::OnCollisionExit(Collider* _other)
{
	owner->OnCollisionExit(_other->getOwner());
	collisionCount--;
}
