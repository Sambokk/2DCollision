#pragma once
class Object;
class GameEngine;


class Scene
{
///�����ڿ� �Ҹ���
public:
	Scene();
	virtual ~Scene();

///�ɹ� ����
protected:
	vector<Object*> objs;
	wstring name;
	GameEngine* gameEngine;

///�ɹ� �Լ�
public:
	virtual void enter(GameEngine* _gameEngine); 
	virtual void exit();

	virtual void update();
	virtual void secondUpdate();
	virtual void thirdUpdate();
	//virtual void render();

	void addObject(Object* _obj) { objs.push_back(_obj); }
	
	vector<Object*> getObjs() { return objs; }

};

