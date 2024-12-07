#include "pch.h"
#include "Background.h"


#include "GameEngine.h"
#include "ResourceManager.h"

Background::Background(GameEngine* _gameEngine, Vector2 _pos)
{
	gameEngine = _gameEngine;
	position = _pos;

	gameEngine->getResourceManager()->loadImage(L"bg", L"..\\Resource\\bg.png");
	texture = gameEngine->getResourceManager()->getImage(L"bg");
	layer = -10;
}

Background::~Background()
{
}

void Background::render(ID2D1HwndRenderTarget* _renderTarget)
{
	D2D1_RECT_F rect = D2D1::RectF(position.x, position.y, position.x + 1400, position.y + 900);
	_renderTarget->DrawBitmap(texture, rect);
}
