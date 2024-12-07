#pragma once
#include "pch.h"
#include "Vector2.h"
#include "Object.h"
#include "Circle.h"
#include "Collider.h"


#include "GameEngine.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "DRD2DEngine.h"

Circle::Circle(GameEngine* _gameEngine, Vector2 _pos, float _r)
	: Object()
{
	radius = _r;
	position = _pos;
	gameEngine = _gameEngine;

	collider = new Collider(this, radius);
}

Circle::Circle(GameEngine* _gameEngine)
	:Object()
{
	gameEngine = _gameEngine;

	std::random_device rd;
	std::mt19937 gen(rd());

	radius = (float)std::uniform_int_distribution<>(50, 110)(gen);
	position.x = (float)std::uniform_int_distribution<>((int)radius + 90, WINDOW_WIDTH - (int)radius - 90)(gen);
	position.y = (float)std::uniform_int_distribution<>((int)radius + 90, WINDOW_HEIGHT - (int)radius - 90)(gen);
	moveSpeed = (float)std::uniform_int_distribution<>(-500, 500)(gen);
	direction.x = (float)std::uniform_int_distribution<>(-10, 10)(gen);
	direction.y = (float)std::uniform_int_distribution<>(-10, 10)(gen);
	direction.normalize();

	collider = new Collider(this, radius);
}

Circle::~Circle()
{
}

void Circle::update()
{
	if (this->name == L"move")
	{
		KeyManager* k = gameEngine->getKeyManager();
		TimeManager* t = gameEngine->getTimeManager();
		float movement = 200.f;

		if (k->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
		{
			position.y = position.y - (movement * t->getDeltaTime());
		}

		if (k->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
		{
			position.y = position.y + (movement * t->getDeltaTime());
		}

		if (k->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
		{
			position.x = position.x - (movement * t->getDeltaTime());
		}

		if (k->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
		{
			position.x = position.x + (movement * t->getDeltaTime());
		}
	}
	
	/*
	string mes = std::to_string(position.x);
	OutputDebugStringA(mes.c_str());
	OutputDebugStringA("\n");
	*/
}

void Circle::render(ID2D1HwndRenderTarget* _renderTarget)
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

	default: //4°³ ÀÌ»ó
	{
		b = gameEngine->getD2DEngine()->getBrush(COLOR::Red);
		D2D1_COLOR_F c = b->GetColor(); c.a = 0.15f;
		_renderTarget->CreateSolidColorBrush(c, &paint);
		break;
	}

	}
	D2D1_ELLIPSE ellipse = { position.x,position.y,radius, radius };
	_renderTarget->DrawEllipse(ellipse, b, 2);
	_renderTarget->FillEllipse(ellipse, paint);
}

void Circle::OnCollisionEnter(Object* _other, Vector2 _depth)
{

}

void Circle::OnCollision(Object* _other, Vector2 _depth)
{
	if (_other->getName() != L"move")
	{
		Vector2 pos = _other->getPosition();
		pos += _depth;
		_other->setPosition(pos);
	}
}

void Circle::OnCollisionExit(Object* _other)
{
}
