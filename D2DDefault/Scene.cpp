#include "pch.h"
#include "Scene.h"

#include "Object.h"
#include "GameEngine.h"

Scene::Scene()
	:gameEngine(nullptr)
{
}

Scene::~Scene()
{

}

void Scene::enter(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
}

void Scene::exit()
{
	for (size_t i = 0; i < objs.size(); i++)
	{
		delete objs[i];
	}
	objs.clear();
}

void Scene::update()
{
	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i]->update();
	}
}

void Scene::secondUpdate()
{
	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i]->secondUpdate();
	}
}

void Scene::thirdUpdate()
{
	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i]->thirdUpdate();
	}
}

/*
void Scene::render()
{
	for (size_t i = 0; i < objs.m_size(); i++)
	{
		objs[i]->render();
	}
}
*/
