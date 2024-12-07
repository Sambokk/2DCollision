#pragma once
#include "define.h"

class Scene;
class GameEngine;

class SceneManager
{
///积己磊客 家戈磊
	SceneManager();
	~SceneManager();

	friend class GameEngine;

///干滚 函荐
	Scene* scenes[(UINT)SCENE_TYPE::END];
	Scene* currentScene;
	GameEngine* gameEngine;

///干滚 窃荐
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

