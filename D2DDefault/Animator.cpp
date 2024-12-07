#include "pch.h"

#include "Animator.h"
#include "GameEngine.h"
#include "Animation.h"
#include "function.h"

Animator::Animator(GameEngine* _gameEngine)
	:owner(nullptr), currentAnimation(nullptr), isRepeat(false)
{
	gameEngine = _gameEngine;
}


Animator::~Animator()
{
	safeDeleteMap(animations);
}


void Animator::createAnimation(const wstring& _name, ID2D1Bitmap* _texture,
	Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount)
{

	Animation* ani = findAnimation(_name);
	assert(ani == nullptr);

	Animation* anime = new Animation(gameEngine);
	anime->setName(_name);
	anime->animator = this;
	anime->createAnimation(_texture, _imgStartPos, _cellSize, _Step, _speed, _cellCount);

	animations.insert(make_pair(_name, anime));
}

Animation* Animator::findAnimation(const wstring& _name)
{
	map<wstring, Animation*>::iterator iter = animations.find(_name);

	if (iter == animations.end())
		return nullptr;

	return iter->second;
}


void Animator::play(const wstring& _name, bool _repeat)
{
	currentAnimation = findAnimation(_name);
	isRepeat = _repeat;
}


void Animator::update()
{
	if (currentAnimation != nullptr)
	{
		currentAnimation->update();
		if (isRepeat && currentAnimation->isAnimationFinished())
		{
			currentAnimation->setFrame(0);
		}
	}
}


void Animator::render(ID2D1HwndRenderTarget* _renderTarget)
{
	if (currentAnimation != nullptr)
		currentAnimation->render(_renderTarget);
}

