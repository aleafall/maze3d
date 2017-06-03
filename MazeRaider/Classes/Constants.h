#ifndef CONSTANTS_H_
#define CONSTANTS_H_

static float cameraY = 10.0f, cameraZ = 15.0f;


enum PropType {
	GOLD_COIN,
	SPEED_UP,
	HIGHT_UP
};

enum PropPos {
	WEST,
	EAST,
	NORTH,
	SOUTH
};


enum tagDirecton {
	ROCKER_CENTER,
	ROCKER_RIGHT,
	ROCKER_UP,
	ROCKER_LEFT,
	ROCKER_DOWN,
};

enum RockerTag
{
	ROCKER_TAG,
	ROCKERBG_TAG,
	PLAYER_TAG,
	CAMERA_TAG,
	MAP_TAG,
	OUTER_TAG,
	POS_TAG,
	MAZE_TAG,
	MINIMAP_TAG,
    AI_TAG,
	MODE_TAG,
	TOLLGAGE_TAG
};

enum AIOrinention{
    AI_WEST,
    AI_EAST,
    AI_NORTH,
    AI_SOUTH
};
#endif
