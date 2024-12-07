#pragma once
#include "Scene.h"
class GameEngine;

class SceneStart : public Scene
{
public:
	SceneStart();
	~SceneStart();

	void enter(GameEngine* _gameEngine) override;
	void exit() override;
	void update() override;
};

