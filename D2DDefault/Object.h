#pragma once
#include "define.h"
#include "Vector2.h"

class GameEngine;
class Collider;
class Rigidbody;
class Animator;

class Object
{
///�����ڿ� �Ҹ���
public:
	Object();
	~Object();

///�ɹ� ����
protected:
	GameEngine* gameEngine;
	
	// �⺻�����ѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	wstring name;
	bool isActive;
	int layer;

	// Transform�ѤѤѤѤѤѤѤѤѤѤѤѤ�
	Vector2 position;
	float rotation;
	vector<Vector2> vertexs;
	vector<Vector2> relativeVertexs;

	// �̵� ���� �ѤѤѤѤѤѤѤѤѤѤѤѤ�
	Vector2 direction; //ũ�� 1�� ���⺤��
	float moveSpeed;
	float rotationSpeed;


///������Ʈ
	ID2D1Bitmap* texture;
	Collider* collider;
	Rigidbody* rigidbody;
	Animator* animator;


///�ɹ� �Լ�
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


	virtual void render(ID2D1HwndRenderTarget* _renderTarget) {} //abstrct : ���������Լ�
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


