#pragma once
#include "Vector2.h"

class GameEngine;
class KeyManager;

class MouseManager
{
///�����ڿ� �Ҹ���
public:
	MouseManager();
	~MouseManager();


/// �ɹ� ����
private:
	GameEngine* gameEngine;
	KeyManager* keyManager;
	HWND hWnd;

	POINT mousePos;			//���� ���콺 ��ġ
	POINT prevMousePos;		//���� ���콺 ��ġ
	Vector2 dxdy;			//�����Ӵ� ���콺 ��ȭ��

///�ɹ� �Լ�
public:
	void initialize(GameEngine* _gameEngine);
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);

	Vector2 getMousePos() { return mousePos; }
	Vector2 getMousedxdy() { return dxdy; }
};

