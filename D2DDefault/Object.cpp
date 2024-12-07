#include "pch.h"
#include "Object.h"

#include "Collider.h"
#include "Rigidbody.h"
#include "Animator.h"

Object::Object()
	:gameEngine(nullptr), position{}, collider(nullptr), name{}, rotation(0), layer(0)
	, isActive(true), moveSpeed(0), rotationSpeed(0), rigidbody(nullptr), animator(nullptr), texture(nullptr)
{
}

Object::~Object()
{
	if (collider != nullptr)
	{
		delete collider;
	}
}

void Object::secondUpdate()
{
	if (collider != nullptr)
	{
		collider->update();
	}
}

void Object::thirdUpdate()
{
	if (rigidbody != nullptr)
	{
		rigidbody->update();
	}
}

void Object::createCollider()
{
	
}

void Object::createAnimator()
{
	animator = new Animator(gameEngine);
	animator->owner = this;
}

void Object::createRigidbody(float _mass, float _fraction)
{
	rigidbody = new Rigidbody(gameEngine, this, _mass, _fraction);
}
