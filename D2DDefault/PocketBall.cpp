#include "pch.h"
#include "PocketBall.h"
#include "GameEngine.h"
#include "DRD2DEngine.h"
#include "Collider.h"
#include "Rigidbody.h"

PocketBall::PocketBall(GameEngine* _gameEngine, BALL_TYPE _type)
{
	gameEngine = _gameEngine;
	d2d = _gameEngine->getD2DEngine();
	type = _type;
	//rotation = 90.f;
	name = L"ball";

	//초기 위치값 설정
	switch (type)
	{
	case BALL_TYPE::C1: //1
		position = Vector2(1000.f, 400.f);
		break;

	case BALL_TYPE::C2: //2
		position = Vector2(1099.f, 381.9f);
		break;

	case BALL_TYPE::C3:
		position = Vector2(1132.f, 400.f);
		break;

	case BALL_TYPE::C4: //3
		position = Vector2(1066.f, 363.9f);
		break;

	case BALL_TYPE::C5:
		position = Vector2(1132.f, 472.2f);
		break;

	case BALL_TYPE::C6:
		position = Vector2(1066.f, 436.1f);
		break;

	case BALL_TYPE::C7: //4
		position = Vector2(1132.f, 327.8f);
		break;

	case BALL_TYPE::L9:
		position = Vector2(1033.f, 381.9f);
		break;

	case BALL_TYPE::L10:
		position = Vector2(1099.f, 418.1f);
		break;

	case BALL_TYPE::L11:
		position = Vector2(1099.f, 454.2f);
		break;

	case BALL_TYPE::L12: //5
		position = Vector2(1099.f, 345.8f);
		break;

	case BALL_TYPE::L13:
		position = Vector2(1132.f, 363.9f);
		break;

	case BALL_TYPE::L14:
		position = Vector2(1033.f, 418.1f);
		break;

	case BALL_TYPE::L15:
		position = Vector2(1132.f, 436.1f);
		break;

	case BALL_TYPE::B:
		position = Vector2(1066.f, 400.f);
		break;

	case BALL_TYPE::W:
		break;
	}

	collider = new Collider(this, radius);
	createRigidbody(10.f, 1.f);
}

PocketBall::~PocketBall()
{
}

void PocketBall::render(ID2D1HwndRenderTarget* _renderTarget)
{
	_renderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(position.x, position.y)));

	D2D1_ELLIPSE outer = { position.x, position.y, radius, radius };
	D2D1_ELLIPSE inner = { position.x, position.y, radius-10, radius-10 };

	float xOffset = -6;
	float xOffset2 = -11;
	float yOffset = -13;
	         
	switch (type)
	{
	case BALL_TYPE::C1:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Gold));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA( L"1", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x+radius, position.y+ yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::C2:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Blue));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA(L"2", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::C3:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Red));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA(L"3", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::C4:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::DarkViolet));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA(L"4", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::C5:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Tomato));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA(L"5", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::C6:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::LimeGreen));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA(L"6", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::C7:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Maroon));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA(L"7", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::L9:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Cornsilk));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::Gold));
		_renderTarget->DrawTextA(L"9", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::L10:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Cornsilk));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::SkyBlue));
		_renderTarget->DrawTextA(L"10", 3,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset2, position.y + yOffset, position.x + 30, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::L11:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Cornsilk));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MistyRose));
		_renderTarget->DrawTextA(L"11", 3,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset2, position.y + yOffset, position.x + 30, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::L12:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Cornsilk));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::PeachPuff));
		_renderTarget->DrawTextA(L"12", 3,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset2, position.y + yOffset, position.x + 30, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::L13:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Cornsilk));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MistyRose));
		_renderTarget->DrawTextA(L"13", 3,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset2, position.y + yOffset, position.x + 30, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::L14:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Cornsilk));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::LightGreen));
		_renderTarget->DrawTextA(L"14", 3,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset2, position.y + yOffset, position.x + 30, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::L15:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Cornsilk));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::RosyBrown));
		_renderTarget->DrawTextA(L"15", 3,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset2, position.y + yOffset, position.x + 30, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::B:
		_renderTarget->FillEllipse(outer, d2d->getBrush(COLOR::Black));
		_renderTarget->FillEllipse(inner, d2d->getBrush(COLOR::MintCream));
		_renderTarget->DrawTextA(L"8", 2,
			gameEngine->getD2DEngine()->getDefaultTextFormat(),
			D2D1::RectF(position.x + xOffset, position.y + yOffset, position.x + radius, position.y + yOffset), //left, top, right, bottom
			gameEngine->getD2DEngine()->getBrush(COLOR::Black));
		break;

	case BALL_TYPE::W:
		break;
	}

	_renderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(position.x, position.y)));
}

void PocketBall::OnCollision(Object* _other, Vector2 _depth)
{
	_other->setPosition(_other->getPosition() + _depth * 0.01f);
}
