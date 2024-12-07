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
///�����ڿ� �Ҹ���
public:
	EventManager();
	~EventManager();


///��� ����
private:
	vector<Event> events;
	vector<Object*> objs_toBeDeleted;
	GameEngine* gameEngine;
	SceneManager* sceneManager;


///�ɹ� �Լ�
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

