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

	animator->createAnimation(L"PlayerWalkDown" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 521)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 10);//�� ����

	animator->createAnimation(L"PlayerWalkUp" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 781)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 10);//�� ����

	animator->createAnimation(L"PlayerWalkLeft" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 651)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 10);//�� ����

	animator->createAnimation(L"PlayerWalkRight" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 911)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 10);//�� ����

	animator->createAnimation(L"PlayerDefaultDown" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 0)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 1);//�� ����

	animator->createAnimation(L"PlayerDefaultLeft" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 131)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 1);//�� ����

	animator->createAnimation(L"PlayerDefaultUp" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 261)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 1);//�� ����

	animator->createAnimation(L"PlayerDefaultRight" //������ų �ִϸ��̼� �̸�
		, gameEngine->getResourceManager()->getImage(L"player") //�ִϸ��̼� ���ҽ�
		, Vector2(0, 391)	//���ҽ����� ���� ��ġ
		, Vector2(120, 130) //�� �ϳ��� ũ��
		, Vector2(120, 0) //�ǳʶ� ũ��
		, 0.1f //��� �ӵ�
		, 1);//�� ����


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

	// �ѤѤ� [ UP ] �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	if (k->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
	{
		animator->play(L"PlayerWalkUp", true);
		position.y = position.y - (movement * t->getDeltaTime());
	}
	
	if (k->GetKeyState(KEY::UP) == KEY_STATE::UP)
		animator->play(L"PlayerDefaultUp", true);
	

	// �ѤѤ� [ DOWN ] �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�	
	if (k->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
	{
		animator->play(L"PlayerWalkDown", true);
		position.y = position.y + (movement * t->getDeltaTime());
	}
		

	if (k->GetKeyState(KEY::DOWN) == KEY_STATE::UP)
		animator->play(L"PlayerDefaultDown", true);


	// �ѤѤ� [ LEFT ] �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
	if (k->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		animator->play(L"PlayerWalkLeft", true);
		position.x = position.x - (movement * t->getDeltaTime());
	}
		
	if (k->GetKeyState(KEY::LEFT) == KEY_STATE::UP)
		animator->play(L"PlayerDefaultLeft", true);


	// �ѤѤ� [ RIGHT ] �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
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
