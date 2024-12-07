#pragma once
#include "Object.h"
class WhiteBall;
class KeyManager;
class MouseManager;
class TimeManager;

class CueStick : public Object
{
///�����ڿ� �Ҹ���
public:
	CueStick(GameEngine* game, Object* ball);
	~CueStick();


///��� ����
private:
	GameEngine* gameEngine;
	Object* whiteBall;
	KeyManager* keyManager;
	TimeManager* timeManager;
	MouseManager* mouseManager;

	Vector2 direction;
	float power;


///�ɹ� �Լ�
public:
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);



};

