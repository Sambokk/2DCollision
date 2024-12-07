#pragma once
class GameEngine;
#include "RigidbodyData.h"

class PhysicsEngine
{
///积己磊客 家戈磊
public:
	PhysicsEngine();
	~PhysicsEngine();
	void initialize(GameEngine* _gameEngine);

///干滚 函荐
private:
	GameEngine* gameEngine;
	vector<RigidbodyData> toExcutes;


///干滚 窃荐
public:
	void update();
	void addToExcutes(RigidbodyData _data) { toExcutes.push_back(_data); }

private:
	void excute();

};

