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
	//그래픽 앤진 초기화
	d2dEngine = new DRD2DEngine;
	d2dEngine->Initialize(hWnd, this);
	d2dEngine->CreateDeviceResources();

	resourceManager = new ResourceManager;
	resourceManager->initialize(this);

	//매니저 초기화
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
		sceneManager->update();			//object 업데이트
		sceneManager->secondUpdate();	//object -> collider 업데이트
		collisionManager->update();		//collider ~> 충돌 판정
		physicsEngine->update();		//물리 연산
		sceneManager->thirdUpdate();	//rigidbody ~> object의 Transform 데이터를 업데이트 시킴.
	}

	d2dEngine->Render();
	eventManager->update();
}
