#include "pch.h"
#include "Rigidbody.h"

#include "Collider.h"
#include "Object.h"
#include "GameEngine.h"
#include "DRD2DEngine.h"
#include "TimeManager.h"

Rigidbody::Rigidbody(GameEngine* _gameEngine, Object* _owner, float _mass, float _fraction)
	:gameEngine(nullptr), owner(nullptr), timeManager(nullptr)
	, linearDrag(), AngularDrag(0), gravityScale(1)
	, useGravity(false), freezeX(false), freezeY(false), freezeRotation(false)
	, angularVelocity(), velocity{}, center{}, type(Rigidbody::TYPE::DYNAMIC)
	, staticFriction(), dynamicFriction()
{
	gameEngine = _gameEngine;
	timeManager = _gameEngine->getTimeManager();
	owner = _owner;
	invMass = 1.f / _mass ;
	mass = _mass;
	//dynamicFriction = _fraction;
	dynamicFriction = 0.4f;

	calcGravityCenter();
}


Rigidbody::~Rigidbody()
{

}

void Rigidbody::update()
{
	//내부
	center = relativeCenter + owner->getPosition();
	velocity *= std::exp(- dynamicFriction * timeManager->getDeltaTime());
 	if (abs(velocity.x) < 1.f) velocity.x = 0;
 	if (abs(velocity.y) < 1.f) velocity.y = 0;

	//외부
	Vector2 p = owner->getPosition();

	p = p + velocity * timeManager->getDeltaTime();
 	owner->setPosition(p);
}

void Rigidbody::render(ID2D1HwndRenderTarget* _renderTarget)
{
	D2D1_ELLIPSE ellipse = { center.x ,center.y ,2, 2 };
	_renderTarget->DrawEllipse(ellipse, gameEngine->getD2DEngine()->getBrush(COLOR::Blue), 2);
}



void Rigidbody::AddForce(Vector2 _force)
{
	//velocity += _force * invMass * timeManager->getDeltaTime();
	velocity += _force; //임시
}

void Rigidbody::AddTorque(float _torque)
{
}

void Rigidbody::calcGravityCenter()
{
	//무게중심 계산
	//원,직사각형 -> 그냥 pos값을 쓰면 됨. 
	///직사각형 최적화해야함!.!

	vector<Vector2> vertexs = owner->getRelativeVertexs();
	if (vertexs.size() == 0)
	{
		relativeCenter = Vector2(0, 0);
	}
	else
	{
		float area = 0;
		for (size_t i = 0; i < vertexs.size(); i++)
		{
			int j = (i + 1) % vertexs.size();

			Vector2 p1 = vertexs[i];
			Vector2 p2 = vertexs[j];

			area += p1.x * p2.y;
			area -= p1.y * p2.x;

			relativeCenter.x += ((p1.x + p2.x) * ((p1.x * p2.y) - (p2.x * p1.y)));
			relativeCenter.y += ((p1.y + p2.y) * ((p1.x * p2.y) - (p2.x * p1.y)));
		}
		area = fabs(area / 2.f);
		relativeCenter = relativeCenter / (6.f * area);
	}
}
