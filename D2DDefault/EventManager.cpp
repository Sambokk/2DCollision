#include "pch.h"
#include "EventManager.h"

#include "Object.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameEngine.h"

EventManager::EventManager()
	:gameEngine(nullptr), sceneManager(nullptr)
{
	
}

EventManager::~EventManager()
{
}

void EventManager::initialize(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
	sceneManager = gameEngine->getSceneManager();
}

void EventManager::update()
{
	//이전 프레임에 등록해둔 삭제될 오브젝트 관리
	for (size_t i = 0; i < objs_toBeDeleted.size(); i++)
	{
		delete objs_toBeDeleted[i];
	}
	objs_toBeDeleted.clear();


	//이번 프레임에 등록된 이벤트 처리
	for (size_t i = 0; i < events.size(); i++)
	{
		Excute(events[i]);
	}
	events.clear();
}

void EventManager::instantiate(Object* _obj)
{
	Event event = { };
	event.eventType = EVENT_TYPE::CREATE_OBJECT;
	event.lParam = (DWORD_PTR)_obj;

	addEvent(event);
}

void EventManager::destroy(Object* _obj)
{
	Event event = { };
	event.eventType = EVENT_TYPE::DELETE_OBJECT;
	event.lParam = (DWORD_PTR)_obj;

	addEvent(event);
}

void EventManager::changeScene(SCENE_TYPE _nextScene)
{
	Event event = { };
	event.eventType = EVENT_TYPE::SCENE_CHANGE;
	event.lParam = (DWORD_PTR)_nextScene;

	addEvent(event);
}

void EventManager::Excute(const Event& _event)
{
	switch (_event.eventType)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		Object* newObj = (Object*)_event.lParam;
		sceneManager->getCurrnetScene()->addObject(newObj);

		break;
	}

	case EVENT_TYPE::DELETE_OBJECT:
	{
		//Object를 비활성 상태로 변경, 삭제 예정인 오브젝트들을 모아둔다.
		Object* inActiveObj = (Object*)_event.lParam;	//lParam : Object Adredd
		inActiveObj->setInactive();
		objs_toBeDeleted.push_back(inActiveObj);

		break;
	}

	case EVENT_TYPE::SCENE_CHANGE:
	{
		//lParma : Next Scene
		sceneManager->changeScene((SCENE_TYPE)_event.lParam);

		break;
	}
	}
}




