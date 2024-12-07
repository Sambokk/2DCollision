#pragma once


class Object;
#include "define.h"
#include "Vector2.h"

class Collider
{
public:

///�����ڿ� �Ҹ���
	Collider(Object* _owner, float _radius); //CIRCLE
	Collider(Object* _owner, float _halfWidth, float _halfHeight, float _rotation); //BOX
	Collider(Object* _owner, vector<Vector2> _vertexs, float _rotation); //CONVEX
	~Collider();

/// �ɹ� ����
private:
	static UINT idIndex;
	UINT id;
	Object* owner;
	UINT collisionCount; //�浹���� �ٸ� �浹ü ����	
	COLLIDER_TYPE type;
	
	//���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	Vector2 position;
	float rotation;
	
	//CIRCLE�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	float radius;

	//CONVEX�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	vector<Vector2> vertexs;


///�ɹ� �Լ�
public:
	void update();

	UINT getID() { return id; }
	Object* getOwner() { return owner; }
	UINT getCollisionCount() { return collisionCount; }
	COLLIDER_TYPE getType() { return type; }

	//���� �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	Vector2 getPosition() { return position; }
	float getRotation() { return rotation; }

	//CIRCLE�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	float getRadius() { return radius; }

	//CONVEX�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	vector<Vector2>getVertexs() { return vertexs; }

public:
	void OnCollisionEnter(Collider* _other, Vector2 depth);
	void OnCollision(Collider* _other, Vector2 depth);
	void OnCollisionExit(Collider* _other);
};

