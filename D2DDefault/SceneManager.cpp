#include "pch.h"
#include "SceneManager.h"

#include "Scene.h"
#include "SceneStart.h"
#include "Stage01.h"

SceneManager::SceneManager()
	:currentScene(nullptr), scenes{}, gameEngine(nullptr)
{
}

SceneManager::~SceneManager()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != scenes[i])
			delete scenes[i];
	}
}

void SceneManager::initialize(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;

	//scene 생성
	scenes[(UINT)SCENE_TYPE::START] = new SceneStart;
	scenes[(UINT)SCENE_TYPE::S01] = new Stage01;


	//시작 scene 지정
	currentScene = scenes[(UINT)SCENE_TYPE::S01];
	currentScene->enter(gameEngine);
}

void SceneManager::update()
{
	currentScene->update();
}

void SceneManager::secondUpdate()
{
	currentScene->secondUpdate();
}

void SceneManager::thirdUpdate()
{
	currentScene->thirdUpdate();
}

void SceneManager::changeScene(SCENE_TYPE _nextScene)
{
	currentScene->exit();
	currentScene = scenes[(UINT)_nextScene];
	currentScene->enter(gameEngine);
}
