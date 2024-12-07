#pragma once
#include "define.h"

class Scene;
class GameEngine;

class SceneManager
{
///�����ڿ� �Ҹ���
	SceneManager();
	~SceneManager();

	friend class GameEngine;

///�ɹ� ����
	Scene* scenes[(UINT)SCENE_TYPE::END];
	Scene* currentScene;
	GameEngine* gameEngine;

///�ɹ� �Լ�
private:
	void initialize(GameEngine* _gameEngine);
	void update();
	void secondUpdate();
	void thirdUpdate();
	//void render();

public:
	Scene* getCurrnetScene() { return currentScene; }
	void changeScene(SCENE_TYPE _nextScene);
};

