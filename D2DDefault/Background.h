#pragma once
#include "Object.h"
class Background : public Object
{
///�����ڿ� �Ҹ���
public:
	Background(GameEngine* _gameEngine, Vector2 _pos);
	~Background();


///�ɹ� ����
private:



///�ɹ� �Լ�
public:
	virtual void render(ID2D1HwndRenderTarget* _renderTarget) override;

};

