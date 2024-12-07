#pragma once

#define WINDOW_HEIGHT 900
#define WINDOW_WIDTH 1400

enum class COLLIDER_TYPE
{
	DEFAULT,

	CIRCLE,
	BOX,
	LINE,
	CONVEX, //볼록 다각형
	CONCAVE, //오목 다각형
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
