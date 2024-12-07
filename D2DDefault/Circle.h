#pragma once
#include "define.h"
#include "Object.h"

class Object;
class Circle : public Object
{
///생성자와 소멸자
public:
	Circle(GameEngine* _gameEngine, Vector2 _pos, float _r);
	Circle(GameEngine* _gameEngine);
	~Circle();

///맴버 변수
private:
	float radius; //반지름
	

///맴버 함수
public:
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;

	void OnCollisionEnter(Object* _other, Vector2 _depth) override;
	void OnCollision(Object* _other, Vector2 _depth) override;
	void OnCollisionExit(Object* _other) override;

	float getRadius() { return radius; }
};

