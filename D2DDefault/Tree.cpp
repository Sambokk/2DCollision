#include "pch.h"
#include "Tree.h"

#include "GameEngine.h"
#include "ResourceManager.h"

Tree::Tree(GameEngine* _gameEngine, Vector2 _pos)
{
	gameEngine = _gameEngine;
	position = _pos;

	gameEngine->getResourceManager()->loadImage(L"tree", L"..\\Resource\\tree.png");
}

Tree::~Tree()
{
}

void Tree::render(ID2D1HwndRenderTarget* _renderTarget)
{
	D2D1_RECT_F rect = D2D1::RectF(position.x - 130, position.y - 390 + 65, position.x + 130, position.y + 65);
	_renderTarget->DrawBitmap(gameEngine->getResourceManager()->getImage(L"tree"), rect);
}
