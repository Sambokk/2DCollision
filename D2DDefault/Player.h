#pragma once
#include "Object.h"

class Player : public Object
{
///积己磊客 家戈磊
public:
	Player(GameEngine* _gameEngine, Vector2 _pos);
	~Player();

///干滚 函荐
private:


///干滚 窃荐
public:
	virtual void update() override;
	virtual void render(ID2D1HwndRenderTarget* _renderTarget) override;

};

