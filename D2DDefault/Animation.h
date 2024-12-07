#pragma once
#include "define.h"
#include "Vector2.h"
class Animator;
class TimeManager;
class GameEngine;

/// <summary>
/// 애니매이션의 한 프레임 정보를 담고 있느 구조체
/// </summary>
struct AnimeFrameInfo
{
	Vector2 leftTop;	//프레임의 좌상단 값
	Vector2 size;		//한 프레임의 크기
	float	speed;		//한 프레임을 출력할 시간
};

/// <summary>
/// 애니매이션 정보를 담고 있는 클래스
/// </summary>
class Animation
{
public:
/// 생성자와 소멸자
	Animation(GameEngine* _gameEngine);
	~Animation();

	friend class Animator;

	
/// 맴버 변수
private:
	TimeManager* timeManager;

	wstring	name;
	Animator* animator;
	
	ID2D1Bitmap* sprite;
	vector<AnimeFrameInfo>	frameInfos;		//모든 프레임 정보
	int						currentFrame;		//현재 프레임
	float					accumulatedTime;	//누적 시간
	bool					isFinished;		//애니메이션 재생이 한번 끝났는가


/// 맴버 함수
private:
	void setName(const wstring& _name) { name = _name; }
	bool isAnimationFinished() { return isFinished; }



public:
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);
	void createAnimation(ID2D1Bitmap* _texture, Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount);

	const wstring& getName() { return name; }

	void setFrame(int _frameIndex)
	{
		isFinished = false;
		currentFrame = _frameIndex;
		accumulatedTime = 0.f;
	}
};