#include "pch.h"
#include "Animation.h"

#include "Animator.h"
#include "Object.h"
#include "TimeManager.h"
#include "GameEngine.h"
#include "TimeManager.h"

Animation::Animation(GameEngine* _gameEngine)
	:animator(nullptr), timeManager(nullptr),
	sprite(nullptr), currentFrame(0), accumulatedTime(0.f), isFinished(false)
{
	timeManager = _gameEngine->getTimeManager();
}

Animation::~Animation()
{

}

void Animation::update()
{
	if (isFinished) return;

	accumulatedTime += timeManager->getDeltaTime();

	if (accumulatedTime > frameInfos[currentFrame].speed)
	{
		currentFrame++;
		if ((int)frameInfos.size() <= currentFrame)
		{
			currentFrame = -1;
			isFinished = true;
			accumulatedTime = 0.f;
			return;
		}
		accumulatedTime -= frameInfos[currentFrame].speed;
	}
}

void Animation::render(ID2D1HwndRenderTarget* _renderTarget)
{
	if (isFinished) return;

	Object* obj = animator->getOwner();
	Vector2 pos = obj->getPosition();


	D2D1_RECT_F rect;
	rect.left = frameInfos[currentFrame].leftTop.x;
	rect.bottom = frameInfos[currentFrame].leftTop.y + frameInfos[currentFrame].size.y;
	rect.right = frameInfos[currentFrame].leftTop.x + frameInfos[currentFrame].size.x;
	rect.top = frameInfos[currentFrame].leftTop.y;

	D2D1_RECT_F positionInfo;
	positionInfo.left = pos.x - frameInfos[currentFrame].size.x / 2;
	positionInfo.right = pos.x + frameInfos[currentFrame].size.x / 2;
	positionInfo.top = pos.y - frameInfos[currentFrame].size.y / 2;
	positionInfo.bottom = pos.y + frameInfos[currentFrame].size.y / 2;

	_renderTarget->DrawBitmap(sprite, positionInfo, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, rect);


// 	HRESULT CopyFromBitmap(
// 		[in, optional] const D2D1_POINT_2U *		//현재 비트맵에서 영역이 복사되는 좌상단,
// 		[in]           ID2D1Bitmap *				//복사할 비트맵
// 		[in, optional] const D2D1_RECT_U * srcRect	//복사할 비트맵의 영역
// 	);


// 	_renderTarget->DrawBitmap(sprite,
// 		(int)pos.x,
// 		(int)pos.y,
// 		(int)frameInfos[currentFrame].leftTop.x,
// 		(int)frameInfos[currentFrame].leftTop.y,
// 		(int)frameInfos[currentFrame].size.x,
// 		(int)frameInfos[currentFrame].size.y,
// 		UnitPixel);
}

void Animation::createAnimation(ID2D1Bitmap* _texture, Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount)
{
	sprite = _texture;

	AnimeFrameInfo frm = {};
	for (UINT i = 0; i < _cellCount; i++)
	{
		frm.speed = _speed;
		frm.size = _cellSize;
		frm.leftTop = _imgStartPos + _Step * (int)i;
		frameInfos.push_back(frm);
	}
}