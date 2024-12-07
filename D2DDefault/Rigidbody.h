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


/// �����ڿ� �Ҹ���
public:
	Rigidbody(GameEngine* _gameEngine, Object* _owner, float _mass, float _fraction);
	~Rigidbody();

	friend class Object;
	friend class PhysicsEngine;

/// �ɹ� ����
private:
	GameEngine* gameEngine;
	TimeManager* timeManager;
	Object* owner;

	//Ư��ġ
	Vector2 center;			// �����߽�
	Vector2 relativeCenter; // ������ ���� �����ǥ

	float mass;				//����
	float invMass;			// ���� ���� 
	float dynamicFriction;	// �̵� ���� ���
	float staticFriction;	// ���� ���� ���
	float linearDrag;		// ������ ���� ~ �Ϲ����� ���� 001(�ܴ��� �ݼ�)�� 10(����)
	float AngularDrag;		// ȸ�� ����
	float gravityScale;		// �߷¿� ������ �޴� ����

	//����
	Vector2 velocity;		// �ӵ�
	float angularVelocity;	// ���ӵ�

	//����
	TYPE type;
	bool useGravity;		// �߷� ��� ����
	bool freezeX;			// X�� ����
	bool freezeY;			// Y�� ����
	bool freezeRotation;	// ȸ�� ����


///�ɹ� �Լ�
public:
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget); //������

	void AddForce(Vector2 _force);
	void AddTorque(float _torque);

	void setType(TYPE _type) { type = _type; }
	Vector2 getVelocity() { return velocity; }

	void setVelocity(Vector2 _v) { velocity = _v; }


private:
	void calcGravityCenter();

};

