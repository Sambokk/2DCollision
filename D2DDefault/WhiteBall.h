#pragma once
#include "Object.h"
class GameEngine;
class DRD2DEngine;

class WhiteBall : public Object
{
/// 积己磊客 家戈磊
public:
	WhiteBall(GameEngine* _gameEngine);
	~WhiteBall();


/// 干滚 函荐
private:
	DRD2DEngine* d2d;
	const float radius = 18.f;

///干滚 窃荐
public:
	void render(ID2D1HwndRenderTarget* _renderTarget);
	void OnCollisionEnter(Object* _other, Vector2 _depth)
	{	}
};

