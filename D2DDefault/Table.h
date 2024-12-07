#pragma once
#include "Object.h"

class GameEngine;

class Table : public Object
{
///积己磊客 家戈磊
public:
	Table(GameEngine* _gameEngine) { gameEngine = _gameEngine; }
	~Table() {}

///干滚 函荐
private:

///干滚 窃荐
public:
	void render(ID2D1HwndRenderTarget* _renderTarget) override;

};

