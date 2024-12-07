#pragma once
#include "define.h"
#include "Vector2.h"
class Animator;
class TimeManager;
class GameEngine;

/// <summary>
/// �ִϸ��̼��� �� ������ ������ ��� �ִ� ����ü
/// </summary>
struct AnimeFrameInfo
{
	Vector2 leftTop;	//�������� �»�� ��
	Vector2 size;		//�� �������� ũ��
	float	speed;		//�� �������� ����� �ð�
};

/// <summary>
/// �ִϸ��̼� ������ ��� �ִ� Ŭ����
/// </summary>
class Animation
{
public:
/// �����ڿ� �Ҹ���
	Animation(GameEngine* _gameEngine);
	~Animation();

	friend class Animator;

	
/// �ɹ� ����
private:
	TimeManager* timeManager;

	wstring	name;
	Animator* animator;
	
	ID2D1Bitmap* sprite;
	vector<AnimeFrameInfo>	frameInfos;		//��� ������ ����
	int						currentFrame;		//���� ������
	float					accumulatedTime;	//���� �ð�
	bool					isFinished;		//�ִϸ��̼� ����� �ѹ� �����°�


/// �ɹ� �Լ�
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