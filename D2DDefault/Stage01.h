#pragma once
#include "Scene.h"

class GameEngine;
class Stage01 : public Scene
{
public:
	Stage01();
	~Stage01();

	void enter(GameEngine* _gameEngine) override;
	void update() override;
	void exit() override;
};

