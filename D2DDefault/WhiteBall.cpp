#include "pch.h"
#include "WhiteBall.h"
#include "Collider.h"
#include "GameEngine.h"
#include "DRD2DEngine.h"
#include "Rigidbody.h"

WhiteBall::WhiteBall(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
	position = Vector2(400, 400);
	d2d = gameEngine->getD2DEngine();

	collider = new Collider(this, radius);
	createRigidbody(10.f, 1.f);
	//rigidbody->setVelocity(Vector2(1500,10));
	name = L"wBall";
}

WhiteBall::~WhiteBall()
{
}

void WhiteBall::render(ID2D1HwndRenderTarget* _renderTarget)
{
	_renderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(position.x, position.y)));

	D2D1_ELLIPSE outer = { position.x, position.y, radius, radius };
	_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::White));
	_renderTarget->DrawTextA(L"𐂂", 2,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(position.x - 9, position.y - 24, position.x + radius, position.y - 13), //left, top, right, bottom
		gameEngine->getD2DEngine()->getBrush(COLOR::Red));

	_renderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(position.x, position.y)));
}
