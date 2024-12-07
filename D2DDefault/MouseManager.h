#pragma once
#include "Vector2.h"

class GameEngine;
class KeyManager;

class MouseManager
{
///생성자와 소멸자
public:
	MouseManager();
	~MouseManager();


/// 맴버 변수
private:
	GameEngine* gameEngine;
	KeyManager* keyManager;
	HWND hWnd;

	POINT mousePos;			//현재 마우스 위치
	POINT prevMousePos;		//이전 마우스 위치
	Vector2 dxdy;			//프레임당 마우스 변화량

///맴버 함수
public:
	void initialize(GameEngine* _gameEngine);
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);

	Vector2 getMousePos() { return mousePos; }
	Vector2 getMousedxdy() { return dxdy; }
};

