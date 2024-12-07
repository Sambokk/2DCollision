#pragma once
#include "Object.h"

class Square : public Object
{
///�����ڿ� �Ҹ���
public:
	Square(GameEngine* _gameEngine);
	Square(GameEngine* _gameEngine, Vector2 _pos, float _halfWidth, float _halfHeight, float _degree);
	~Square();


///�ɹ� ����
private:
	float halfWidth;	//�ʺ�
	float halfHeight;	//����

///�ɹ� �Լ�
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;

	void OnCollisionEnter(Object* _other, Vector2 _depth) override;


	float getHalfWidth() { return halfWidth; }
	float getHalfHeight() { return halfHeight; }
};

