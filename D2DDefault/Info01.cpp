#include "pch.h"
#include "Info01.h"

#include "GameEngine.h"
#include "DRD2DEngine.h"

Info01::Info01(GameEngine* _g)
{
	gameEngine = _g;
}

Info01::~Info01()
{
}

void Info01::render(ID2D1HwndRenderTarget* _renderTarget)
{	
	_renderTarget->DrawTextA(
		L"▊▊▊  0", 7,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(25, 20, 200, 100),
		gameEngine->getD2DEngine()->getBrush(COLOR::LightBlue)
	);

	_renderTarget->DrawTextA(
		L"▊▊▊  1", 7,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(25, 50, 200, 100),
		gameEngine->getD2DEngine()->getBrush(COLOR::SpringGreen)
	);

	_renderTarget->DrawTextA(
		L"▊▊▊  2", 7,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(25, 80, 200, 100),
		gameEngine->getD2DEngine()->getBrush(COLOR::Yellow)
	);

	_renderTarget->DrawTextA(
		L"▊▊▊  3", 7,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(25, 110, 200, 200),
		gameEngine->getD2DEngine()->getBrush(COLOR::Orange)
	);

	_renderTarget->DrawTextA(
		L"▊▊▊  4≤ ", 8,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(25, 140, 200, 200),
		gameEngine->getD2DEngine()->getBrush(COLOR::Red)
	);

	_renderTarget->DrawTextA(
		L"SPACE : 일시정지", 12,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(1150, 25, 1500, 200),
		gameEngine->getD2DEngine()->getBrush(COLOR::White)
	);

	_renderTarget->DrawTextA(
		L"TAP : 다시로드", 10,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(1150, 835, 1500, 900),
		gameEngine->getD2DEngine()->getBrush(COLOR::White)
	);
}
