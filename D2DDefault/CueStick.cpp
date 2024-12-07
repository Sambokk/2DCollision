#include "pch.h"
#include "CueStick.h"

#include "WhiteBall.h"
#include "GameEngine.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "DRD2DEngine.h"
#include "Rigidbody.h"
#include "TimeManager.h"

CueStick::CueStick(GameEngine* game, Object* ball)
	:gameEngine(nullptr), whiteBall(nullptr), mouseManager(nullptr), keyManager(nullptr)
	, power(0), direction()
{
	gameEngine = game;
	mouseManager = gameEngine->getMouseManager();
	keyManager = gameEngine->getKeyManager();
	timeManager = gameEngine->getTimeManager();
	whiteBall = ball;
}

CueStick::~CueStick()
{
}

void CueStick::update()
{
	//마우스 좌표로 큐대 회전
	Vector2 mousePos = mouseManager->getMousePos();
	Vector2 ballPos = whiteBall->getPosition();
	
	//57.29577951 (rad to deg)
	
	direction = mousePos - ballPos;
	direction.normalize();

	rotation = atan2(mousePos.x - ballPos.x, -(mousePos.y - ballPos.y));
	rotation *= (float)57.29577951;
	rotation -= 90;

	//오른쪽 마우스를 눌리고 있을 때(차지)
	if (keyManager->GetKeyState(KEY::Z) == KEY_STATE::HOLD)
	{
		if (2000 > power)
		{
			power += 2000 * timeManager->getDeltaTime();
		}
	}

	if (keyManager->GetKeyState(KEY::X) == KEY_STATE::HOLD)
	{
		power -= 2000 * timeManager->getDeltaTime();
		if (power < 0) power = 0;
	}


	//왼쪽 버튼을 눌렀을 때(발사)
	if (keyManager->GetKeyState(KEY::LMOUSE) == KEY_STATE::DOWN)
	{
		whiteBall->getRigidbody()->AddForce(-direction * power);
		power = 0;
	}
}

void CueStick::render(ID2D1HwndRenderTarget* _renderTarget)
{
	Vector2 v = whiteBall->getRigidbody()->getVelocity();
	if (abs(v.x) < 0.1 && abs(v.y) < 0.1)
	{
		Vector2 ballPos = whiteBall->getPosition();
		float offset = power * (float)0.05;

		_renderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(ballPos.x, ballPos.y)));

		_renderTarget->DrawRectangle(D2D1_RECT_F{ ballPos.x + 20 + offset, ballPos.y - 5, ballPos.x + 200 + offset, ballPos.y + 5 } //left, top, right, botton
		, gameEngine->getD2DEngine()->getBrush(COLOR::Beige), 2.f);

		_renderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(whiteBall->getPosition().x, whiteBall->getPosition().y)));
	}

	wchar_t str[100];
	swprintf_s(str, L" Power : Z, X\n Roatate : Mouse\n Hit : L Mouse\n\n Reset : R\n 흰 공이 빠졌을 때 L Mouse 클릭");

	_renderTarget->DrawTextA(
		str,
		wcslen(str),
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(10, 720, 500, 770),
		gameEngine->getD2DEngine()->getBrush(COLOR::LightBlue)
	);

	_renderTarget->DrawTextA(
		L" * 다중충돌, 스핀 계산 x",
		16,
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(1170, 870, 1400, 900),
		gameEngine->getD2DEngine()->getBrush(COLOR::LightBlue)
	);

}
