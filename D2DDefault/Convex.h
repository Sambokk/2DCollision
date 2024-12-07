#pragma once
#include "Object.h"

class Convex : public Object
{
///�����ڿ� �Ҹ���
public:
	Convex(GameEngine* _gameEngine);
	Convex(GameEngine* _gameEngine, vector<Vector2> _vertex);
	~Convex();


///��� ����
private:

///��� �Լ�
public:
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;
	
	void OnCollisionEnter(Object* _other, Vector2 _depth) override;
	void OnCollision(Object* _other, Vector2 _depth) override;
};

