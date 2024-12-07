#pragma once

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1400

enum class COLLIDER_TYPE
{
	DEFAULT,

	CIRCLE,
	BOX,
	LINE,
	CONVEX, //���� �ٰ���
	CONCAVE, //���� �ٰ���
};

enum class SCENE_TYPE
{
	START,
	S01,
	S02,
	S03,

	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END
};
