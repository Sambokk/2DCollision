#pragma once
class GameEngine;

/// <summary>
/// 게임의 시간을 관리
/// </summary>
class TimeManager
{
public:
///생성자와 소멸자
	TimeManager();
	~TimeManager();

private:
/// 맴버 변수

	GameEngine* gameEngine;

	LARGE_INTEGER currentCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER frequency;


	unsigned int frameCount;
	double frameTime;

	unsigned int fps;
	double deltaTime;

	
///맴버 함수
public:
	void initialize(GameEngine* _gameEngine);
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);

	float getDeltaTime() { return (float) deltaTime; }
};

