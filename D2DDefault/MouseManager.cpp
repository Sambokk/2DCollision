#include "pch.h"
#include "MouseManager.h"

#include "KeyManager.h"
#include "GameEngine.h"
#include "DRD2DEngine.h"

MouseManager::MouseManager()
	:gameEngine(nullptr), keyManager(nullptr), prevMousePos{}, mousePos{}, hWnd(NULL)
{
}

MouseManager::~MouseManager()
{
}

void MouseManager::initialize(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
	keyManager = _gameEngine->getKeyManager();
	hWnd = _gameEngine->gethWnd();

	GetCursorPos(&prevMousePos);
	ScreenToClient(hWnd, &prevMousePos);
}

void MouseManager::update()
{
	GetCursorPos(&mousePos);
	ScreenToClient(hWnd, &mousePos);

	dxdy = Vector2( float(mousePos.x - prevMousePos.x), float(mousePos.y - prevMousePos.y));
	prevMousePos = mousePos;
}

void MouseManager::render(ID2D1HwndRenderTarget* _renderTarget)
{
	wchar_t str[60];
	swprintf_s(str, L"x: %d\n y: %d", mousePos.x,mousePos.y);

	_renderTarget->DrawTextA(
		str,
		wcslen(str),
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(mousePos.x, mousePos.y, mousePos.x + 100, mousePos.y+100),
		gameEngine->getD2DEngine()->getBrush(COLOR::LightBlue)
	);
}
