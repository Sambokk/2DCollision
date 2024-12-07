#pragma once
#include "Object.h"

class Square : public Object
{
///생성자와 소멸자
public:
	Square(GameEngine* _gameEngine);
	Square(GameEngine* _gameEngine, Vector2 _pos, float _halfWidth, float _halfHeight, float _degree);
	~Square();


///맴버 변수
private:
	float halfWidth;	//너비
	float halfHeight;	//높이

///맴버 함수
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;

	void OnCollisionEnter(Object* _other, Vector2 _depth) override;


	float getHalfWidth() { return halfWidth; }
	float getHalfHeight() { return halfHeight; }
};

