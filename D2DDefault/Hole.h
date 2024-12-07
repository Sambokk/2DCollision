#pragma once
#include "Object.h"

class EventManager;
class Hole : public Object
{
///积己磊客 家戈磊
public:
	Hole(GameEngine* _gameEngine, Vector2 _pos);
	~Hole();


///干滚 函荐
private:
	EventManager* eventManager;
	bool isWhiteBall;
	Object* wball;
	static int ballCount;

///干滚 窃荐
public:
	void update() override;
	void render(ID2D1HwndRenderTarget* _renderTarget) override;
	void OnCollisionEnter(Object* _other, Vector2 _depth) override;

};

