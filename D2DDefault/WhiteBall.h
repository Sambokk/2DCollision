#pragma once
#include "Object.h"
class GameEngine;
class DRD2DEngine;

class WhiteBall : public Object
{
/// �����ڿ� �Ҹ���
public:
	WhiteBall(GameEngine* _gameEngine);
	~WhiteBall();


/// �ɹ� ����
private:
	DRD2DEngine* d2d;
	const float radius = 18.f;

///�ɹ� �Լ�
public:
	void render(ID2D1HwndRenderTarget* _renderTarget);
	void OnCollisionEnter(Object* _other, Vector2 _depth)
	{	}
};

