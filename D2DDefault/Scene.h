#pragma once
class Object;
class GameEngine;


class Scene
{
///积己磊客 家戈鲤
public:
	Scene();
	virtual ~Scene();

///干滚 函荐
protected:
	vector<Object*> objs;
	wstring name;
	GameEngine* gameEngine;

///干滚 窃荐
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

