#pragma once
#include "Object.h"

class EventManager;
class Hole : public Object
{
///�����ڿ� �Ҹ���
public:
	Hole(GameEngine* _gameEngine, Vector2 _pos);
	~Hole();


///�ɹ� ����
private:
	EventManager* eventManager;
	bool isWhiteBall;
	Object* wball;
	static int ballCount;

///�ɹ� �Լ�
public:
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;
	void OnCollisionEnter(Object* _other, Vector2 _depth) override;

};

