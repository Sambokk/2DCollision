#pragma once
#include "Object.h"
class Background : public Object
{
///积己磊客 家戈磊
public:
	Background(GameEngine* _gameEngine, Vector2 _pos);
	~Background();


///干滚 函荐
private:



///干滚 窃荐
public:
	virtual void render(ID2D1HwndRenderTarget* _renderTarget) override;

};

