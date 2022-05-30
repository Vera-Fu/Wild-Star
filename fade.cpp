//---------------------------------------------------------------
//fade.cpp
//
//												ì¬ŽÒFFU YIZHI
//												ì¬“úF2021/7/05
//---------------------------------------------------------------
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "UI.h"
#include "sound.h"

unsigned int g_FadeTexture;
float g_alpha;
FADEMODE g_fademode;

void InitFade()
{
	g_alpha = 0.0f;
	g_fademode = FADEMODE_NONE;
}

void UninitFade()
{

}

void UpdateFade()
{
	switch (g_fademode)
	{
	case FADEMODE_NONE:
		break;
	case FADEMODE_OUT:
		SetVolumeBGM(0, 120);
		g_alpha += 0.02f;

		if (g_alpha >= 1.0f)
		{
			g_fademode = FADEMODE_IN;

			SCENE scene = GetScene();
			switch (scene)
			{
			case SCENE_TITLE:
				SetScene(SCENE_LEVEL);
				break;
			case SCENE_LEVEL:
				SetScene(SCENE_GAME);
				break;
			case SCENE_GAME:
				SetScene(SCENE_RESULT);
				break;
			case SCENE_RESULT:
				SetScene(SCENE_TITLE);
				break;
			default:
				break;
			}
		}
		break;
	case FADEMODE_IN:
		SetVolumeBGM(1, 120);
		g_alpha -= 0.02f;

		if (g_alpha <= 0.0f)
		{
			g_fademode = FADEMODE_NONE;
		}
		break;
	default:
		break;
	}
}

void DrawFade()
{
	SetTexture(NULL);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(0.0f, 0.0f, 0.0f, g_alpha));
}

bool SetFade(FADEMODE m)
{
	if (g_fademode == FADEMODE_NONE)
	{
		g_fademode = m;
		if (m == FADEMODE_OUT)
		{
			g_alpha = 0.0f;
		}
		else if (m == FADEMODE_IN)
		{
			g_alpha = 1.0f;
		}
		return true;
	}
	return false;
}


