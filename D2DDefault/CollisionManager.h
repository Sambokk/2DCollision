#pragma once
#include "define.h"
#include "CollisionData.h"
#include "Vector2.h"
class Collider;
class GameEngine;
class PhysicsEngine;

union COLLIDER_ID
{
	struct
	{
		UINT  left_ID;
		UINT  right_ID;
	};
	ULONGLONG ID;
};


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

private:
	GameEngine* gameEngine;
	PhysicsEngine* physicsEngine;

	map<ULONGLONG, bool> collisionInfos;
	vector<Vector2> forRenders;
	vector<Vector2> mPoints;

public:
	void initialize(GameEngine* _gameEngine);
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);

	void setPhysicsEngine(PhysicsEngine* _engine) { physicsEngine = _engine; }

private:
	void detectCollision();
	CollisionData isCollision(Collider* _iCollider, Collider* _jCollider);
	CollisionData CC(Collider* _iCollider, Collider* _jCollider);
	CollisionData GJK(Collider* _iCollider, Collider* _jCollider);
};

