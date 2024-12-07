#pragma once
#include "define.h"

class Object;
class GameEngine;
class SceneManager;

struct Event
{
	EVENT_TYPE eventType;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};


class EventManager
{
///생성자와 소멸자
public:
	EventManager();
	~EventManager();


///멤버 변수
private:
	vector<Event> events;
	vector<Object*> objs_toBeDeleted;
	GameEngine* gameEngine;
	SceneManager* sceneManager;


///맴버 함수
public:
	void initialize(GameEngine* _gameEngine);
	void update();
	void addEvent(const Event& _event) { events.push_back(_event); }
	
	void instantiate(Object* _obj);
	void destroy(Object* _obj);
	void changeScene(SCENE_TYPE _nextScene);


private:
	void Excute(const Event& _event);

};

