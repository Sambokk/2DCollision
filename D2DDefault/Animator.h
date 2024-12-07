#pragma once
#include "Vector2.h"
class Object;
class Animation;
class GameEngine;

class Animator
{
///�����ڿ� �Ҹ���
	Animator(GameEngine* _gameEngine);
	~Animator();

	friend class Object;

/// �ɹ� ����
private:
	GameEngine* gameEngine;
	Object* owner;

	Animation* currentAnimation;
	map<wstring, Animation*> animations;

	bool isRepeat;


///�ɹ� �Լ�
public:
	Object*		getOwner() { return owner; }
	void		createAnimation(const wstring& _name, ID2D1Bitmap* _texture, Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount);
	Animation*  findAnimation(const wstring& _name);
	void		play(const wstring& _name, bool _repeat);

	void		render(ID2D1HwndRenderTarget* _renderTarget);
	void		update();

};

