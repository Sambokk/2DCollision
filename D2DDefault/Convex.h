#pragma once
#include "Object.h"

class Convex : public Object
{
///생성자와 소멸자
public:
	Convex(GameEngine* _gameEngine);
	Convex(GameEngine* _gameEngine, vector<Vector2> _vertex);
	~Convex();


///멤버 변수
private:

///멤버 함수
public:
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;
	
	void OnCollisionEnter(Object* _other, Vector2 _depth) override;
	void OnCollision(Object* _other, Vector2 _depth) override;
};

