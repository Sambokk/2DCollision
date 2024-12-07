#pragma once
class GameEngine;
#include "RigidbodyData.h"

class PhysicsEngine
{
///�����ڿ� �Ҹ���
public:
	PhysicsEngine();
	~PhysicsEngine();
	void initialize(GameEngine* _gameEngine);

///�ɹ� ����
private:
	GameEngine* gameEngine;
	vector<RigidbodyData> toExcutes;


///�ɹ� �Լ�
public:
	void update();
	void addToExcutes(RigidbodyData _data) { toExcutes.push_back(_data); }

private:
	void excute();

};

