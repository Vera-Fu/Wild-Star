#pragma once

#include "system.h"

#include <vector>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

enum class Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

typedef enum
{
	SCENE_TITLE = 0,
	SCENE_LEVEL,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_MAX
}SCENE;

void SetScene(SCENE scene);
SCENE GetScene(void);
bool GetIsTouch(Float2 touch, float sizex, float sizey, float posx, float posy);

void SetUninit(void);