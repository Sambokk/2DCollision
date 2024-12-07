#include "pch.h"
#include "PhysicsEngine.h"
#include "RigidbodyData.h"
#include "Rigidbody.h"
#include "function.h"

PhysicsEngine::PhysicsEngine()
	:gameEngine(nullptr)
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::initialize(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
}

void PhysicsEngine::update()
{
	for (const RigidbodyData &a : toExcutes)
	{
		if (a.r1->type == Rigidbody::TYPE::STATIC)
		{
			Vector2 n = a.depth;
			n.normalize();

			Vector2 v = a.r2->velocity;
			a.r2->velocity = v + n * 2 * Dot(v, n);
			
		}
		
		else if (a.r1->mass == a.r2->mass)
		{
			Vector2& v1 = a.r1->velocity;
			Vector2& v2 = a.r2->velocity;
			Vector2& x1 = a.r1->center;
			Vector2& x2 = a.r2->center;

			float i = SignedDot((v1 - v2), (x1 - x2)) / (float)pow(Distance(x1, x2), 2);
			Vector2 v1f = v1 - (x1 - x2) * i;
			
			i =		  SignedDot((v2 - v1), (x2 - x1)) / (float)pow(Distance(x2, x1), 2);
			Vector2 v2f = v2 - (x2 - x1) * i;

			v1 = v1f;
			v2 = v2f;
		}
		else
		{

		}
	}
	toExcutes.clear();
}

void PhysicsEngine::excute()
{

}
