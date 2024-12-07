#pragma once
#include "Object.h"


class Info01 : public Object
{
public:
	Info01(GameEngine* _g);
	~Info01();

public:
	void render(ID2D1HwndRenderTarget* _renderTarget) override;
};

