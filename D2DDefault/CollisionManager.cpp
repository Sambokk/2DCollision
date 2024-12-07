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
			//�浹ü�� ���� ��� ��ŵ
			if (objs[i]->getCollider() == nullptr
				|| objs[j]->getCollider() == nullptr)
				continue;

			Collider* iCollider = objs[i]->getCollider();
			Collider* jCollider = objs[j]->getCollider();

			//�� �浹ü ���̵� ���� i + j 			
			COLLIDER_ID colliderID = {};
			colliderID.left_ID = iCollider->getID();
			colliderID.right_ID = jCollider->getID();

			iter = collisionInfos.find(colliderID.ID);

			//�浹 ID�� ������ ���� ����
			if (collisionInfos.end() == iter)
			{
				collisionInfos.insert(make_pair(colliderID.ID, false));
				iter = collisionInfos.find(colliderID.ID);
			}

			CollisionData collision = isCollision(iCollider, jCollider);
			//�浹���� ���
			if (collision.isCollision == true)
			{
				//���� O ���� O
				if (iter->second)
				{
					iCollider->OnCollision(jCollider, collision.depth);
					jCollider->OnCollision(iCollider, collision.depth * -1);
					continue;
				}

				//���� X ���� O
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

			//�浹���� ���� ���
			else
			{
				//���� O ���� X
				if (iter->second)
				{
					iCollider->OnCollisionExit(jCollider);
					jCollider->OnCollisionExit(iCollider);
					iter->second = false;
					continue;
				}
				//���� X ���� X
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
	//Simplex�� ����Ʈ(vertex)���� �迭��, �ִ� ������ 3���̴�.
	Simplex2D points;
	
	//������ ���⺤��(1,0,0)���κ��� �ʱ� supportingPoint�� ���Ѵ�.
	Vector3 support = SupportingPoint(_iCollider, _jCollider,Vector3(1,0,0));
	points.push_front(support);

	//���ο� ���⺤�ʹ� ������ ���Ѵ�.
	Vector3 direction = (support * -1).normalize();

	//�ٸ� supporting Point���� ���Ѵ�. 
	//(Ż�� ���� : finds a vertex that was already the furthest one along it.)
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
