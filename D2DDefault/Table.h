#pragma once
#include "Object.h"

class GameEngine;

class Table : public Object
{
///�����ڿ� �Ҹ���
public:
	Table(GameEngine* _gameEngine) { gameEngine = _gameEngine; }
	~Table() {}

///�ɹ� ����
private:

///�ɹ� �Լ�
public:
	void render(ID2D1HwndRenderTarget* _renderTarget) override;

};

