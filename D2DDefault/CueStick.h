#pragma once
#include "Object.h"
class WhiteBall;
class KeyManager;
class MouseManager;
class TimeManager;

class CueStick : public Object
{
///생성자와 소멸자
public:
	CueStick(GameEngine* game, Object* ball);
	~CueStick();


///멤버 변수
private:
	GameEngine* gameEngine;
	Object* whiteBall;
	KeyManager* keyManager;
	TimeManager* timeManager;
	MouseManager* mouseManager;

	Vector2 direction;
	float power;


///맴버 함수
public:
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);



};

