#include "pch.h"
#include "TimeManager.h"
#include "DRD2DEngine.h"
#include "GameEngine.h"

TimeManager::TimeManager()
	:currentCount{}, prevCount{}, frequency{}
	, fps(), deltaTime(), frameCount(), frameTime()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::initialize(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&prevCount);
}

void TimeManager::update()
{
	QueryPerformanceCounter(&currentCount);

	//deltaTime
	deltaTime = (currentCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;
	prevCount = currentCount;


	//fps
	++frameCount;
	frameTime += deltaTime;

	if (frameTime >= 1.f)
	{
		fps = frameCount;
		frameCount = 0;
		frameTime = 0.0;

// 		wchar_t buffer[255] = {};
// 		swprintf_s(buffer, L"fps : %d", fps);
	}
}

void TimeManager::render(ID2D1HwndRenderTarget* _renderTarget)
{
	wchar_t str[50];
	swprintf_s(str, L"fps : %d", fps);

	_renderTarget->DrawTextA(
		str,
		wcslen(str),
		gameEngine->getD2DEngine()->getDefaultTextFormat(),
		D2D1::RectF(10, 10, 200, 50),
		gameEngine->getD2DEngine()->getBrush(COLOR::LightBlue)
	);
}
