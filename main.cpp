#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "sound.h"
#ifdef WIN32
#include "fps_limit.h"
#endif // WIN32

// ここからinclude
#include "titlebg.h"
#include "levelbg.h"
#include "resultbg.h"

#include "title.h"
#include "levelchoose.h"
#include "game.h"
#include "result.h"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"

#include "fade.h"
#include "UI.h"

void Init();
void Uninit();
void Update();
void Draw();

SCENE g_scene;

extern "C" void nnMain()
{
	Init();

#ifdef WIN32
	InitFpsLimiter();
#endif // WIN32

	while (true)
	{
#ifdef WIN32
		UpdateFpsLimiter();
#endif // WIN32

		Update();
		Draw();

#ifdef WIN32
		DoFpsLimit();
#endif // WIN32
	}

	Uninit();
}


void Init()
{
	InitSound();
	InitSystem();

	// 後ろ向きを描画しない（通常設定）
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// 頂点が反時計回りならば前（通常設定）
	glFrontFace(GL_CCW);

	InitController();

	// ここからInit
	InitFade();
	InitUI();

	g_scene = SCENE_TITLE;

	switch (g_scene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_LEVEL:
		InitLevelChoose();
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_RESULT:
		InitResult();
		break;
	default:
		break;
	}

	SetFade(FADEMODE_IN);

	//PlayBGM(STRM_GAME_BGM);
}


void Uninit()
{
	// ここからUninit
	switch (g_scene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_LEVEL:
		UninitLevelChoose();
		break;
	case SCENE_GAME:
		UninitGame();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	default:
		break;
	}
	UninitFade();
	UninitUI();

	UninitSound();
	UninitController();
	UninitSystem();
}


void Update()
{
	UpdateController();
	UpdateSound();

	// ここからUpdate
	UpdateFade();
	UpdateUI();
	switch (g_scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_LEVEL:
		UpdateLevelChoose();
		break;
	case SCENE_GAME:
		UpdateGame();
		break;
	case SCENE_RESULT:
		UpdateResult();
		break;
	default:
		break;
	}
}


void Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ここからDraw

	switch (g_scene)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_LEVEL:
		DrawLevelChoose();
		break;
	case SCENE_GAME:
		DrawGame();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;
	default:
		break;
	}
	DrawFade();
	DrawUI();

	SwapBuffers();
}

void SetScene(SCENE scene)
{
	switch (g_scene)
	{
	case SCENE_TITLE:
		//InitTitle();
		UninitTitle();
		InitLevelChoose();
		break;
	case SCENE_LEVEL:
		UninitLevelChoose();
		InitGame();
		break;
	case SCENE_GAME:
		UninitGame();
		InitResult();
		break;
	case SCENE_RESULT:
		UninitResult();
		InitTitle();
		break;
	default:
		break;
	}
	g_scene = scene;
}

SCENE GetScene(void)
{
	return g_scene;
}

bool GetIsTouch(Float2 touch, float sizex, float sizey, float posx, float posy)
{
	if (touch.x > posx - (sizex / 2) &&
		touch.x < posx + (sizex / 2) &&
		touch.y > posy - (sizey / 2) &&
		touch.y < posy + (sizey / 2))
	{
		return true;
	}
	return false;
}

void SetUninit(void)
{
	Uninit();
}
