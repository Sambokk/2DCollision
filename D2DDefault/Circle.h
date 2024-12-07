#pragma once
#include "define.h"
#include "Object.h"

class Object;
class Circle : public Object
{
///�����ڿ� �Ҹ���
public:
	Circle(GameEngine* _gameEngine, Vector2 _pos, float _r);
	Circle(GameEngine* _gameEngine);
	~Circle();

///�ɹ� ����
private:
	float radius; //������
	

///�ɹ� �Լ�
public:
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;

	void OnCollisionEnter(Object* _other, Vector2 _depth) override;
	void OnCollision(Object* _other, Vector2 _depth) override;
	void OnCollisionExit(Object* _other) override;

	float getRadius() { return radius; }
};

