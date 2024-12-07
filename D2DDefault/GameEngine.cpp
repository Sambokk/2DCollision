#pragma once
#include "pch.h"
#include "GameEngine.h"

#include "TimeManager.h"
#include "CollisionManager.h"
#include "DRD2DEngine.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "PhysicsEngine.h"
#include "MouseManager.h"

GameEngine::GameEngine(HWND _hWnd)
	:collisionManager(nullptr), timeManager(nullptr), keyManager(nullptr)
	, sceneManager(nullptr), eventManager(nullptr), resourceManager(nullptr)
	, d2dEngine(nullptr) ,physicsEngine(nullptr), mouseManager(nullptr)
	, hWnd(nullptr), isPaused(false)
{
	hWnd = _hWnd;
}

GameEngine::~GameEngine()
{
}

void GameEngine::initialize()
{
	//�׷��� ���� �ʱ�ȭ
	d2dEngine = new DRD2DEngine;
	d2dEngine->Initialize(hWnd, this);
	d2dEngine->CreateDeviceResources();

	resourceManager = new ResourceManager;
	resourceManager->initialize(this);

	//�Ŵ��� �ʱ�ȭ
	physicsEngine = new PhysicsEngine;
	physicsEngine->initialize(this);

	collisionManager = new CollisionManager;
	collisionManager->initialize(this);

	keyManager = new KeyManager;
	keyManager->initialize();
	
	mouseManager = new MouseManager;
	mouseManager->initialize(this);

	timeManager = new TimeManager;
	timeManager->initialize(this);

	sceneManager = new SceneManager;
	sceneManager->initialize(this);

	eventManager = new EventManager;
	eventManager->initialize(this);
}

void GameEngine::finalize()
{
	delete d2dEngine;
	delete collisionManager;
	delete timeManager;
	delete sceneManager;
	delete keyManager;
	delete resourceManager;
	delete mouseManager;
	delete physicsEngine;
	delete eventManager;
}

void GameEngine::progress()
{
	timeManager->update();
	keyManager->update();
	mouseManager->update();
	
	if (keyManager->GetKeyState(KEY::SPACE) == KEY_STATE::UP)
		isPaused = !isPaused;

	if (!isPaused)
	{
		sceneManager->update();			//object ������Ʈ
		sceneManager->secondUpdate();	//object -> collider ������Ʈ
		collisionManager->update();		//collider ~> �浹 ����
		physicsEngine->update();		//���� ����
		sceneManager->thirdUpdate();	//rigidbody ~> object�� Transform �����͸� ������Ʈ ��Ŵ.
	}

	d2dEngine->Render();
	eventManager->update();
}
