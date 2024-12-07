#pragma once
#include "Object.h"
class GameEngine;
class DRD2DEngine;

enum class BALL_TYPE
{
	//���� (���, �Ķ�, ����, ����, ��Ȳ, �ʷ�, ����)
	C1, C2, C3, C4, C5, C6, C7,
	
	//�ٰ�
	L9, L10, L11, L12, L13, L14, L15,
	
	//���, ������
	B, W
};


class PocketBall : public Object
{
///�����ڿ� �Ҹ���
public:
	PocketBall(GameEngine* _gameEngine, BALL_TYPE _type);
	~PocketBall();

///�ɹ� ����
private:
	BALL_TYPE type;
	const float radius = 18.f;
	DRD2DEngine* d2d;

///�ɹ� �Լ�
public:
	void render(ID2D1HwndRenderTarget* _renderTarget) override;
	void OnCollision(Object* _other, Vector2 _depth) override;
};

