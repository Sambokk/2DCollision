#pragma once
class GameEngine;

/// <summary>
/// ������ �ð��� ����
/// </summary>
class TimeManager
{
public:
///�����ڿ� �Ҹ���
	TimeManager();
	~TimeManager();

private:
/// �ɹ� ����

	GameEngine* gameEngine;

	LARGE_INTEGER currentCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER frequency;


	unsigned int frameCount;
	double frameTime;

	unsigned int fps;
	double deltaTime;

	
///�ɹ� �Լ�
public:
	void initialize(GameEngine* _gameEngine);
	void update();
	void render(ID2D1HwndRenderTarget* _renderTarget);

	float getDeltaTime() { return (float) deltaTime; }
};

