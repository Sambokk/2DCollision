#pragma once
#include "Object.h"

class Player : public Object
{
///�����ڿ� �Ҹ���
public:
	Player(GameEngine* _gameEngine, Vector2 _pos);
	~Player();

///�ɹ� ����
private:


///�ɹ� �Լ�
public:
	virtual void update() override;
	virtual void render(ID2D1HwndRenderTarget* _renderTarget) override;

};

