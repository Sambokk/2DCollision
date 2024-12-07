#include "pch.h"
#include "Vector2.h"
#include "Stage01.h"
#include "Scene.h"
#include "define.h"
#include "GameEngine.h"
#include "EventManager.h"
#include "GameEngine.h"
#include "KeyManager.h"

#include "Convex.h"
#include "Circle.h"
#include "PocketBall.h"
#include "Table.h"
#include "WhiteBall.h"
#include "CueStick.h"
#include "Hole.h"

Stage01::Stage01()
{
}

Stage01::~Stage01()
{
}

void Stage01::enter(GameEngine	* _gameEngine)
{
	gameEngine = _gameEngine;
	
	Object* table = new Table(_gameEngine);
	addObject(table);
	
	Object* h1 = new Hole(_gameEngine, Vector2(125, 125));
	Object* h2 = new Hole(_gameEngine, Vector2(700, 125));
	Object* h3 = new Hole(_gameEngine, Vector2(1275, 125));
	Object* h4 = new Hole(_gameEngine, Vector2(125, 675));
	Object* h5 = new Hole(_gameEngine, Vector2(700, 675));
	Object* h6 = new Hole(_gameEngine, Vector2(1275, 675));
	addObject(h1);
	addObject(h2);
	addObject(h3);
	addObject(h4);
	addObject(h5);
	addObject(h6);



	Object* top1 = new Convex(_gameEngine,
		{ Vector2(140,100), Vector2(675,100), Vector2(660,150), Vector2(190,150)}); //70
	addObject(top1);

	Object* top2 = new Convex(_gameEngine,
		{ Vector2(725,100), Vector2(1260,100), Vector2(1210,150), Vector2(740,150) });
	addObject(top2);


	Object* down1 = new Convex(_gameEngine,
		{ Vector2(140,700), Vector2(675,700), Vector2(660,650), Vector2(190,650) });
	addObject(down1);

	Object* down2 = new Convex(_gameEngine,
		{ Vector2(725,700), Vector2(1260,700), Vector2(1210,650), Vector2(740,650) });
	addObject(down2);



	Object* left = new Convex(_gameEngine,
		{ Vector2(100,140), Vector2(150,190), Vector2(150,610), Vector2(100,660) });
	addObject(left);

	Object* right = new Convex(_gameEngine,
		{ Vector2(1300,140), Vector2(1250,190), Vector2(1250,610), Vector2(1300,660) });
	addObject(right);

	//

	Object* c1 = new PocketBall(_gameEngine, BALL_TYPE::C1);
	addObject(c1);

	Object* c2 = new PocketBall(_gameEngine, BALL_TYPE::C2);
	addObject(c2);

	Object* c3 = new PocketBall(_gameEngine, BALL_TYPE::C3);
	addObject(c3);

	Object* c4 = new PocketBall(_gameEngine, BALL_TYPE::C4);
	addObject(c4);

	Object* c5 = new PocketBall(_gameEngine, BALL_TYPE::C5);
	addObject(c5);

	Object* c6 = new PocketBall(_gameEngine, BALL_TYPE::C6);
	addObject(c6);

	Object* c7 = new PocketBall(_gameEngine, BALL_TYPE::C7);
	addObject(c7);
	
	//
	
	Object* l9 = new PocketBall(_gameEngine, BALL_TYPE::L9);
	addObject(l9);

	Object* c10 = new PocketBall(_gameEngine, BALL_TYPE::L10);
	addObject(c10);

	Object* c11 = new PocketBall(_gameEngine, BALL_TYPE::L11);
	addObject(c11);

	Object* c12 = new PocketBall(_gameEngine, BALL_TYPE::L12);
	addObject(c12);

	Object* c13 = new PocketBall(_gameEngine, BALL_TYPE::L13);
	addObject(c13);

	Object* c14 = new PocketBall(_gameEngine, BALL_TYPE::L14);
	addObject(c14);

	Object* c15 = new PocketBall(_gameEngine, BALL_TYPE::L15);
	addObject(c15);

	//
	
	Object* b = new PocketBall(_gameEngine, BALL_TYPE::B);
	addObject(b);

	Object* w = new WhiteBall(_gameEngine);
	addObject(w);
	
	Object* stick = new CueStick(_gameEngine, w);
	addObject(stick);


}

void Stage01::update()
{
	Scene::update();
	if (gameEngine->getKeyManager()->GetKeyState(KEY::NUM0) == KEY_STATE::UP)
	{
		gameEngine->getEventManager()->changeScene(SCENE_TYPE::START);
	}

	if (gameEngine->getKeyManager()->GetKeyState(KEY::R) == KEY_STATE::UP)
	{
		gameEngine->getEventManager()->changeScene(SCENE_TYPE::S01);
	}


}

void Stage01::exit()
{	
	Scene::exit();
}
