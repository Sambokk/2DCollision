#pragma once
#include "Object.h"
class GameEngine;
class DRD2DEngine;

enum class BALL_TYPE
{
	//색공 (노랑, 파랑, 빨강, 보라, 주황, 초록, 갈색)
	C1, C2, C3, C4, C5, C6, C7,
	
	//줄공
	L9, L10, L11, L12, L13, L14, L15,
	
	//흰공, 검은공
	B, W
};


class PocketBall : public Object
{
///생성자와 소멸자
public:
	PocketBall(GameEngine* _gameEngine, BALL_TYPE _type);
	~PocketBall();

///맴버 변수
private:
	BALL_TYPE type;
	const float radius = 18.f;
	DRD2DEngine* d2d;

///맴버 함수
public:
	void render(ID2D1HwndRenderTarget* _renderTarget) override;
	void OnCollision(Object* _other, Vector2 _depth) override;
};

