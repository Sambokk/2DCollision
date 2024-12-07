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
/// ������ ����, ����, ���Ḧ �Ѱ��Ѵ�.
/// </summary>
class GameEngine
{

///�����ڿ� �Ҹ���
public:
	GameEngine(HWND _hWnd);
	~GameEngine();

///�ɹ� ����
private:
	
	//�Ŵ���
	CollisionManager* collisionManager;
	TimeManager* timeManager;
	KeyManager* keyManager;
	DRD2DEngine* d2dEngine;
	SceneManager* sceneManager;
	EventManager* eventManager;
	ResourceManager* resourceManager;
	PhysicsEngine* physicsEngine;
	MouseManager* mouseManager;

	//����
	HWND hWnd; //���� ������ �ڵ�

	bool isPaused;

///�ɹ� �Լ�
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

