#pragma once
#define _USE_MATH_DEFINES

#include "Vector2.h"
#include "Vector3.h"
#include "Simplex2D.h"
#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "GameEngine.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "function.h"
#include "DRD2DEngine.h"
#include "gjkSupport.h"
#include "CollisionData.h"
#include "PhysicsEngine.h"
#include "RigidbodyData.h"

CollisionManager::CollisionManager()
	:gameEngine(nullptr), physicsEngine(nullptr)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::initialize(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
	physicsEngine = gameEngine->getPhysicsEngine();
}

void CollisionManager::update()
{
	detectCollision();
}

void CollisionManager::detectCollision()
{
	const vector<Object*>& objs =
		gameEngine->getSceneManager()->getCurrnetScene()->getObjs();

	map<ULONGLONG, bool>::iterator iter;
	
	if (objs.size() == 0) return;
	for (size_t i = 0; i < objs.size() - 1; i++)
	{
		for (size_t j = i + 1; j < objs.size(); j++)
		{
			//충돌체가 없는 경우 스킵
			if (objs[i]->getCollider() == nullptr
				|| objs[j]->getCollider() == nullptr)
				continue;

			Collider* iCollider = objs[i]->getCollider();
			Collider* jCollider = objs[j]->getCollider();

			//두 충돌체 아이디 생성 i + j 			
			COLLIDER_ID colliderID = {};
			colliderID.left_ID = iCollider->getID();
			colliderID.right_ID = jCollider->getID();

			iter = collisionInfos.find(colliderID.ID);

			//충돌 ID가 없으면 새로 생성
			if (collisionInfos.end() == iter)
			{
				collisionInfos.insert(make_pair(colliderID.ID, false));
				iter = collisionInfos.find(colliderID.ID);
			}

			CollisionData collision = isCollision(iCollider, jCollider);
			//충돌했을 경우
			if (collision.isCollision == true)
			{
				//이전 O 현재 O
				if (iter->second)
				{
					iCollider->OnCollision(jCollider, collision.depth);
					jCollider->OnCollision(iCollider, collision.depth * -1);
					continue;
				}

				//이전 X 현재 O
				else
				{
					iCollider->OnCollisionEnter(jCollider, collision.depth);
					jCollider->OnCollisionEnter(iCollider, collision.depth * -1);
					iter->second = true;
					
					Rigidbody* r1 = iCollider->getOwner()->getRigidbody();
					Rigidbody* r2 = jCollider->getOwner()->getRigidbody();
					if (r1 != nullptr && r2 != nullptr)
					{
						physicsEngine->addToExcutes(RigidbodyData(r1, r2, collision.depth));
					}
					
					continue;
				}
			}

			//충돌하지 않은 경우
			else
			{
				//이전 O 현재 X
				if (iter->second)
				{
					iCollider->OnCollisionExit(jCollider);
					jCollider->OnCollisionExit(iCollider);
					iter->second = false;
					continue;
				}
				//이전 X 현재 X
			}
		}
	}
}

CollisionData CollisionManager::isCollision(Collider* _iCollider, Collider* _jCollider)
{
 	//CC
	if (_iCollider->getType() == COLLIDER_TYPE::CIRCLE
		&& _jCollider->getType() == COLLIDER_TYPE::CIRCLE)
	{
		return CC(_iCollider, _jCollider);
	}

	//Convex(Polygon)
	if ((_iCollider->getType() == COLLIDER_TYPE::CONVEX || _iCollider->getType() == COLLIDER_TYPE::CIRCLE)
			&& (_jCollider->getType() == COLLIDER_TYPE::CONVEX || _jCollider->getType() == COLLIDER_TYPE::CIRCLE))
	{
		return GJK(_iCollider, _jCollider);
	}


	return false;
}

CollisionData CollisionManager::CC(Collider* _iCollider, Collider* _jCollider)
{
	Vector2 posi = _iCollider->getPosition();
	Vector2 posj = _jCollider->getPosition();
	float ri = _iCollider->getRadius();
	float rj = _jCollider->getRadius();

	float distance = Distance(posi, posj);
	if (distance <= (ri + rj))
	{
		Vector2 depth = posj - posi;
		return CollisionData(true, depth);
	}
	return CollisionData(false);
}


CollisionData CollisionManager::GJK(Collider* _iCollider, Collider* _jCollider)
{		
	//Simplex는 포인트(vertex)들의 배열로, 최대 갯수는 3개이다.
	Simplex2D points;
	
	//임의의 방향벡터(1,0,0)으로부터 초기 supportingPoint를 구한다.
	Vector3 support = SupportingPoint(_iCollider, _jCollider,Vector3(1,0,0));
	points.push_front(support);

	//새로운 방향벡터는 원점을 향한다.
	Vector3 direction = (support * -1).normalize();

	//다른 supporting Point들을 구한다. 
	//(탈출 조건 : finds a vertex that was already the furthest one along it.)
	while (true)
	{
		support = SupportingPoint(_iCollider, _jCollider, direction);
		if (SignedDot(support, direction) <= 0)
			return CollisionData(false); //no collision
		
		points.push_front(support);

		if (NextSimplex2D(points, direction))
		{
			vector<Vector2> polytope;
			for (int i = 0; i < 3; i++)
			{
				polytope.push_back(Vector2(points[i].x, points[i].y));
			}

			Vector2 collisionPoint = EPA(polytope, _iCollider, _jCollider);
			return CollisionData(true, collisionPoint);
		}	
	}
}

void CollisionManager::render(ID2D1HwndRenderTarget* _renderTarget)
{
	/*
	D2D1_RECT_F horizon;
	horizon.left = -500;
	horizon.top = 1;
	horizon.right = 500;
	horizon.bottom = -1;

	_renderTarget->DrawRectangle(horizon,
		gameEngine->getD2DEngine()->getBrush(COLOR::MistyRose), 2.f);
	
	D2D1_RECT_F vertical;
	vertical.left = -1;
	vertical.top = 500;
	vertical.right = 1;
	vertical.bottom = -500;

	_renderTarget->DrawRectangle(vertical,
		gameEngine->getD2DEngine()->getBrush(COLOR::MistyRose), 2.f);
	
	for (size_t i = 0; i < forRenders.size(); i++)
	{
		D2D1_ELLIPSE ellipse1 = { forRenders[i].x, forRenders[i].y,2, 2 };
		_renderTarget->DrawEllipse(ellipse1, gameEngine->getD2DEngine()->getBrush(COLOR::Red), 3);
	}
	*/
}
