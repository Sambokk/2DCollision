#pragma once
#include "Object.h"


class Tree : public Object
{
	///�����ڿ� �Ҹ���
public:
	Tree(GameEngine* _gameEngine, Vector2 _pos);
	~Tree();


	///�ɹ� ����
private:



	///�ɹ� �Լ�
public:
	virtual void render(ID2D1HwndRenderTarget* _renderTarget) override;
};

