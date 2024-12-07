#include "pch.h"
#include "Hole.h"

#include "Collider.h"
#include "GameEngine.h"
#include "EventManager.h"
#include "DRD2DEngine.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "WhiteBall.h"
#include "Rigidbody.h"

int Hole::ballCount = 0;

Hole::Hole(GameEngine* _gameEngine, Vector2 _pos)
	:eventManager(nullptr), isWhiteBall(false), wball(nullptr)
{
	gameEngine = _gameEngine;
	eventManager = _gameEngine->getEventManager();
	position = _pos;

	collider = new Collider(this, 10);
}

Hole::~Hole()
{

}

void Hole::update()
{
	if (isWhiteBall == true)
	{
		if (gameEngine->getKeyManager()->GetKeyState(KEY::LMOUSE) == KEY_STATE::DOWN)
		{
			Vector2 pos = gameEngine->getMouseManager()->getMousePos();
			if (175 < pos.x && pos.x < 1225 && 175 < pos.y && pos.y < 625)
			{
				isWhiteBall = false;
				wball->setPosition(pos);
			}
		}
	}

	if (gameEngine->getKeyManager()->GetKeyState(KEY::R) == KEY_STATE::DOWN)
	{
		ballCount = 0;
	}
}

void Hole::render(ID2D1HwndRenderTarget* _renderTarget)
{
	D2D1_ELLIPSE ellipse = { position.x,position.y,25, 25 };
	_renderTarget->FillEllipse(ellipse, gameEngine->getD2DEngine()->getBrush(COLOR::Black));
}

void Hole::OnCollisionEnter(Object* _other, Vector2 _depth)
{
	if (_other->getName() == L"wBall")
	{
		isWhiteBall = true;
		wball = _other;
		wball->getRigidbody()->setVelocity(Vector2(0, 0));
		_other->setPosition(Vector2(0, -1000));
	}
	else
	{
		_other->setPosition(Vector2(1270 - 45 * ballCount, 740));
		_other->getRigidbody()->setVelocity(Vector2(0, 0));
		ballCount++;
	}
}
