#pragma once


class Object;
#include "define.h"
#include "Vector2.h"

class Collider
{
public:

///생성자와 소멸자
	Collider(Object* _owner, float _radius); //CIRCLE
	Collider(Object* _owner, float _halfWidth, float _halfHeight, float _rotation); //BOX
	Collider(Object* _owner, vector<Vector2> _vertexs, float _rotation); //CONVEX
	~Collider();

/// 맴버 변수
private:
	static UINT idIndex;
	UINT id;
	Object* owner;
	UINT collisionCount; //충돌중인 다른 충돌체 갯수	
	COLLIDER_TYPE type;
	
	//공통 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	Vector2 position;
	float rotation;
	
	//CIRCLEㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	float radius;

	//CONVEXㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	vector<Vector2> vertexs;


///맴버 함수
public:
	void update();

	UINT getID() { return id; }
	Object* getOwner() { return owner; }
	UINT getCollisionCount() { return collisionCount; }
	COLLIDER_TYPE getType() { return type; }

	//공통 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	Vector2 getPosition() { return position; }
	float getRotation() { return rotation; }

	//CIRCLEㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	float getRadius() { return radius; }

	//CONVEXㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	vector<Vector2>getVertexs() { return vertexs; }

public:
	void OnCollisionEnter(Collider* _other, Vector2 depth);
	void OnCollision(Collider* _other, Vector2 depth);
	void OnCollisionExit(Collider* _other);
};

