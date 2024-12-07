#define _USE_MATH_DEFINES
#include "pch.h"
#include "Square.h"
#include "Vector2.h"

#include "GameEngine.h"
#include "Object.h"
#include "Collider.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "DRD2DEngine.h"

#include "function.h"

Square::Square(GameEngine* _gameEngine)
	:Object(), halfHeight(0), halfWidth(0)
{
	gameEngine = _gameEngine;

	
	std::random_device rd;
	std::mt19937 gen(rd());

	halfWidth = (float)std::uniform_int_distribution<>(40, 100)(gen);
	halfHeight = (float)std::uniform_int_distribution<>(40, 100)(gen);

	float dist = Distance(Vector2(halfHeight, 0.f), Vector2(0.f, halfWidth));
	position.x = (float)std::uniform_int_distribution<>((int)dist + 90, WINDOW_WIDTH - (int)dist - 90)(gen);
	position.y = (float)std::uniform_int_distribution<>((int)dist + 90, WINDOW_HEIGHT - (int)dist - 90)(gen);
	
	rotation = (float)std::uniform_int_distribution<>(0, 359)(gen);
	rotationSpeed = (float)std::uniform_int_distribution<>(-100, 100)(gen);
	moveSpeed = (float)std::uniform_int_distribution<>(-500, 500)(gen);
	
	direction.x = (float)std::uniform_int_distribution<>(-10, 10)(gen);
	direction.y = (float)std::uniform_int_distribution<>(-10, 10)(gen);
	direction.normalize();
	

	collider = new Collider(this, halfWidth, halfHeight, rotation);
}

Square::Square(GameEngine* _gameEngine, Vector2 _pos, float _halfWidth, float _halfHeight, float _degree)
	:Object()
{
	gameEngine = _gameEngine;
	position = _pos;
	halfHeight = _halfHeight;
	halfWidth = _halfWidth;
	rotation = _degree;

	collider = new Collider(this, halfWidth, halfHeight, rotation);
}

Square::~Square()
{
}

void Square::update()
{
	float dt = gameEngine->getTimeManager()->getDeltaTime();

	rotation += rotationSpeed * dt;
	rotation = fmod(rotation, 360.f); //오버플로 방지용 
	position = position + direction * moveSpeed * dt;
}

void Square::render(ID2D1HwndRenderTarget* _renderTarget)
{
	ID2D1SolidColorBrush* b = nullptr;
	ID2D1SolidColorBrush* paint = nullptr;

	switch (collider->getCollisionCount())
	{
		case 3: 
		{
			b = gameEngine->getD2DEngine()->getBrush(COLOR::Orange);
			D2D1_COLOR_F c = b->GetColor(); c.a = 0.15f;
			_renderTarget->CreateSolidColorBrush(c, &paint);
			break;
		}

		case 2: 
		{
			b = gameEngine->getD2DEngine()->getBrush(COLOR::Yellow);
			D2D1_COLOR_F c = b->GetColor(); c.a = 0.15f;
			_renderTarget->CreateSolidColorBrush(c, &paint);
			break;
		}

		case 1:
		{
			b = gameEngine->getD2DEngine()->getBrush(COLOR::SpringGreen);
			D2D1_COLOR_F c = b->GetColor(); c.a = 0.15f;
			_renderTarget->CreateSolidColorBrush(c, &paint);
			break;
		}

		case 0:
		{
			b = gameEngine->getD2DEngine()->getBrush(COLOR::LightBlue);
			D2D1_COLOR_F c = b->GetColor(); c.a = 0.15f;
			_renderTarget->CreateSolidColorBrush(c, &paint);
			break;
		}

		default: //4개 이상
		{
			b = gameEngine->getD2DEngine()->getBrush(COLOR::Red);
			D2D1_COLOR_F c = b->GetColor(); c.a = 0.15f;
			_renderTarget->CreateSolidColorBrush(c, &paint);
			break;
		}

	}

	D2D1_RECT_F rect;
	rect.left = position.x - halfWidth;
	rect.top = position.y - halfHeight;
	rect.right = position.x + halfWidth;
	rect.bottom = position.y + halfHeight;

	//회전된 사각형일 때
	if (rotation != 0)
	{
		_renderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(position.x, position.y)));

		_renderTarget->DrawRectangle(rect, b, 2.f);
		_renderTarget->FillRectangle(rect, paint);

		_renderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(position.x, position.y)));
	}
	//회전된 사각형이 아닐 때
	else
	{
		_renderTarget->DrawRectangle(rect, b, 2.f);
		_renderTarget->FillRectangle(rect, paint);
	}
}

void Square::OnCollisionEnter(Object* _other, Vector2 _depth)
{
	//위쪽 벽에 닿았을 때
	if (_other->getName() == L"upBoundary")
	{
		direction.y *= -1;
		position.y += 2 ;
	}

	//아래쪽 벽에 닿았을 때
	if (_other->getName() == L"downBoundary")
	{
		direction.y *= -1;
		position.y -= 2;
	}

	//왼쪽 벽에 닿았을 때
	if (_other->getName() == L"leftBoundary")
	{
		direction.x *= -1;
		position.x += 2;
	}

	//오른쪽 벽에 닿았을 때
	if (_other->getName() == L"rightBoundary")
	{
		direction.x *= -1;
		position.x -= 2;
	}
}

