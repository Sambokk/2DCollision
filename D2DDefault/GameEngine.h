#pragma once


class DRD2DEngine;
class CollisionManager;
class TimeManager;
class KeyManager;
class SceneManager;
class EventManager;
class ResourceManager;
class PhysicsEngine;
class MouseManager;

class Object;

/// <summary>
/// 게임의 실행, 진행, 종료를 총괄한다.
/// </summary>
class GameEngine
{

///생성자와 소멸자
public:
	GameEngine(HWND _hWnd);
	~GameEngine();

///맴버 변수
private:
	
	//매니저
	CollisionManager* collisionManager;
	TimeManager* timeManager;
	KeyManager* keyManager;
	DRD2DEngine* d2dEngine;
	SceneManager* sceneManager;
	EventManager* eventManager;
	ResourceManager* resourceManager;
	PhysicsEngine* physicsEngine;
	MouseManager* mouseManager;

	//변수
	HWND hWnd; //메인 윈도우 핸들

	bool isPaused;

///맴버 함수
public:
	void initialize();
	void finalize();
	void progress();

	HWND gethWnd() { return hWnd; }

	SceneManager* getSceneManager() { return sceneManager; }
	KeyManager* getKeyManager() { return keyManager; }
	TimeManager* getTimeManager() { return timeManager; }
	DRD2DEngine* getD2DEngine() { return d2dEngine; }
	EventManager* getEventManager() { return eventManager; }
	CollisionManager* getCollisionManager() { return collisionManager; }
	ResourceManager* getResourceManager() { return resourceManager; }
	PhysicsEngine* getPhysicsEngine() { return physicsEngine; }
	MouseManager* getMouseManager() { return mouseManager; }
};

