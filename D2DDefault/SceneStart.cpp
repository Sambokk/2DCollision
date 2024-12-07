#include "pch.h"

#include "SceneStart.h"

#include "GameEngine.h"
#include "Stage01.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "EventManager.h"
#include "Object.h"

#include "Player.h"
#include "Background.h"
#include "Tree.h"

SceneStart::SceneStart()
{
}

SceneStart::~SceneStart()
{
}

void SceneStart::enter(GameEngine* _gameEngine)
{
 	gameEngine = _gameEngine;

	Object* bg = new Background(_gameEngine, Vector2(0, 0));
	addObject(bg);

	Object* p = new Player(_gameEngine, Vector2(700, 450));
	addObject(p);

	Object* tree = new Tree(_gameEngine, Vector2(700, 400));
	addObject(tree);

}

void SceneStart::exit()
{
	Scene::exit();
}

void SceneStart::update()
{
	Scene::update();

	if(gameEngine->getKeyManager()->GetKeyState(KEY::TAB) == KEY_STATE::UP)
	{
		gameEngine->getEventManager()->changeScene(SCENE_TYPE::START);
	}

	if (gameEngine->getKeyManager()->GetKeyState(KEY::NUM1) == KEY_STATE::UP)
	{
		gameEngine->getEventManager()->changeScene(SCENE_TYPE::S01);
	}
}
