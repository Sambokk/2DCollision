#pragma once
#include "define.h"
#include "Vector2.h"

class GameEngine;
class Collider;
class Rigidbody;
class Animator;

class Object
{
///생성자와 소멸자
public:
	Object();
	~Object();

///맴버 변수
protected:
	GameEngine* gameEngine;
	
	// 기본정보ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	wstring name;
	bool isActive;
	int layer;

	// Transformㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	Vector2 position;
	float rotation;
	vector<Vector2> vertexs;
	vector<Vector2> relativeVertexs;

	// 이동 관련 ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	Vector2 direction; //크기 1의 방향벡터
	float moveSpeed;
	float rotationSpeed;


///컴포넌트
	ID2D1Bitmap* texture;
	Collider* collider;
	Rigidbody* rigidbody;
	Animator* animator;


///맴버 함수
public:
	void			setName(wstring _name)	{ name = _name; }
	wstring			getName()				{ return name; }
	void			setInactive()			{ isActive = false; }
	void			setLayer(int _index)	{ layer = _index; }
	int				getLayer()				{ return layer; }

	void			setPosition(Vector2 _pos) { position = _pos; }
	Vector2			getPosition()			{ return position; }
	float			getRotation()			{ return rotation; }
	vector<Vector2> getVertexs()			{ return vertexs; }
	vector<Vector2> getRelativeVertexs()	{ return relativeVertexs; }


	Collider* getCollider()	{ return collider; }
	Rigidbody* getRigidbody() { return rigidbody; }


	virtual void render(ID2D1HwndRenderTarget* _renderTarget) {} //abstrct : 순수가상함수
	virtual void update() {}
	virtual void secondUpdate();
	virtual void thirdUpdate();

	virtual void OnCollisionEnter(Object* _other, Vector2 _depth) {}
	virtual void OnCollision(Object* _other, Vector2 _depth) {}
	virtual void OnCollisionExit(Object* _other) {}

	void setTexture(ID2D1Bitmap* _texture) { texture = _texture; }
	void createCollider();
	void createAnimator();
	void createRigidbody(float _mass, float _fraction);

};


