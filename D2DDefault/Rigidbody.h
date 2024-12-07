#pragma once
#include "Vector2.h"

class GameEngine;
class Object;
class Collider;
class PhysicsEngine;
class TimeManager;

class Rigidbody
{
public:
	enum class TYPE
	{
		STATIC,
		DYNAMIC
	};


/// 생성자와 소멸자
public:
	Rigidbody(GameEngine* _gameEngine, Object* _owner, float _mass, float _fraction);
	~Rigidbody();

	friend class Object;
	friend class PhysicsEngine;

/// 맴버 변수
private:
	GameEngine* gameEngine;
	TimeManager* timeManager;
	Object* owner;

	//특성치
	Vector2 center;			// 무게중심
	Vector2 relativeCenter; // 중점에 대한 상대좌표

	float mass;				//질량
	float invMass;			// 질량 역수 
	float dynamicFriction;	// 이동 마찰 계수
	float staticFriction;	// 정지 마찰 계수
	float linearDrag;		// 움직임 저항 ~ 일반적인 값은 001(단단한 금속)과 10(깃털)
	float AngularDrag;		// 회전 저항
	float gravityScale;		// 중력에 영향을 받는 정도

	//변량
	Vector2 velocity;		// 속도
	float angularVelocity;	// 각속도

	//제한
	TYPE type;
	bool useGravity;		// 중력 사용 여부
	bool freezeX;			// X축 고정
	bool freezeY;			// Y축 고정
	bool freezeRotation;	// 회전 고정


///맴버 함수
public:
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget); //디버깅용

	void AddForce(Vector2 _force);
	void AddTorque(float _torque);

	void setType(TYPE _type) { type = _type; }
	Vector2 getVelocity() { return velocity; }

	void setVelocity(Vector2 _v) { velocity = _v; }


private:
	void calcGravityCenter();

};

