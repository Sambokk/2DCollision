#include "pch.h"
#include "Player.h"

#include "KeyManager.h"
#include "GameEngine.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Animator.h"

Player::Player(GameEngine* _gameEngine, Vector2 _pos)
{
	gameEngine = _gameEngine;
	position = _pos;

	gameEngine->getResourceManager()->loadImage(L"player", L"..\\Resource\\link.png");
	
	createAnimator();

	animator->createAnimation(L"PlayerWalkDown" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 521)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 10);//셀 갯수

	animator->createAnimation(L"PlayerWalkUp" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 781)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 10);//셀 갯수

	animator->createAnimation(L"PlayerWalkLeft" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 651)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 10);//셀 갯수

	animator->createAnimation(L"PlayerWalkRight" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 911)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 10);//셀 갯수

	animator->createAnimation(L"PlayerDefaultDown" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 0)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 1);//셀 갯수

	animator->createAnimation(L"PlayerDefaultLeft" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 131)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 1);//셀 갯수

	animator->createAnimation(L"PlayerDefaultUp" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 261)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 1);//셀 갯수

	animator->createAnimation(L"PlayerDefaultRight" //생성시킬 애니메이션 이름
		, gameEngine->getResourceManager()->getImage(L"player") //애니메이션 리소스
		, Vector2(0, 391)	//리소스에서 시작 위치
		, Vector2(120, 130) //셀 하나의 크기
		, Vector2(120, 0) //건너뛸 크기
		, 0.1f //재생 속도
		, 1);//셀 갯수


	animator->play(L"PlayerDefaultDown", true);
}

Player::~Player()
{
}

void Player::update()
{
	KeyManager* k = gameEngine->getKeyManager();
	TimeManager* t = gameEngine->getTimeManager();
	float movement = 300.f;

	// ㅡㅡㅡ [ UP ] ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (k->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	{
		animator->play(L"PlayerWalkUp", true);
		position.y = position.y - (movement * t->getDeltaTime());
	}
	
	if (k->GetKeyState(KEY::UP) == KEY_STATE::UP)
		animator->play(L"PlayerDefaultUp", true);
	

	// ㅡㅡㅡ [ DOWN ] ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ	
	if (k->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		animator->play(L"PlayerWalkDown", true);
		position.y = position.y + (movement * t->getDeltaTime());
	}
		

	if (k->GetKeyState(KEY::DOWN) == KEY_STATE::UP)
		animator->play(L"PlayerDefaultDown", true);


	// ㅡㅡㅡ [ LEFT ] ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (k->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		animator->play(L"PlayerWalkLeft", true);
		position.x = position.x - (movement * t->getDeltaTime());
	}
		
	if (k->GetKeyState(KEY::LEFT) == KEY_STATE::UP)
		animator->play(L"PlayerDefaultLeft", true);


	// ㅡㅡㅡ [ RIGHT ] ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	if (k->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		animator->play(L"PlayerWalkRight", true);
		position.x = position.x + (movement * t->getDeltaTime());
	}
		
	if (k->GetKeyState(KEY::RIGHT) == KEY_STATE::UP)
		animator->play(L"PlayerDefaultRight", true);


	if(animator != nullptr)
		animator->update();
}

void Player::render(ID2D1HwndRenderTarget* _renderTarget)
{
	if (animator != nullptr)
		animator->render(_renderTarget);

	else
	{
		D2D1_RECT_F rect = D2D1::RectF(position.x, position.y, position.x + 120, position.y + 130);
		_renderTarget->DrawBitmap(gameEngine->getResourceManager()->getImage(L"player"), rect);
	}
}
