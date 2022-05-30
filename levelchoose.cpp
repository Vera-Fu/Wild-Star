#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "fade.h"
#include "levelchoose.h"
#include "levelchoosebg.h"
#include "shop.h"
#include "UI.h"
#include "sound.h"

unsigned int g_LevelChooseTexture[LEVEL_MAX];

bool isleveltouch;

LEVEL g_level[LEVEL_MAX];

void InitLevelChoose()
{
	InitLevelChooseBG();
	
	g_LevelChooseTexture[LEVEL_01] = LoadTexture("rom:/level_01.tga");
	g_LevelChooseTexture[LEVEL_02] = LoadTexture("rom:/level_02.tga");
	g_LevelChooseTexture[LEVEL_03] = LoadTexture("rom:/level_03.tga");
	g_LevelChooseTexture[LEVEL_04] = LoadTexture("rom:/level_04.tga");


	for (int i = 0; i < LEVEL_MAX; i++)
	{
		g_level[i].pos = MakeFloat2(0.0f, 0.0f);
		g_level[i].size = MakeFloat2(LEVELCHOOSESIZE, LEVELCHOOSESIZE);
		g_level[i].rank = C;
		g_level[i].isBossDefeted = false;
		g_level[i].isUse = false;
		g_level[i].isChoose = false;
	}
	SetLevel(MakeFloat2(-700.0f, +200.0f), LEVEL_01);
	g_level[LEVEL_01].isUnlock = true;
	SetLevel(MakeFloat2(-200.0f, +400.0f), LEVEL_02);
	SetLevel(MakeFloat2(+400.0f, -100.0f), LEVEL_03);
	SetLevel(MakeFloat2(+700.0f, -300.0f), LEVEL_04);

	isleveltouch = false;

	InitShop();
}


void UninitLevelChoose()
{
	UninitLevelChooseBG();
	
	for (int i = 0; i < LEVEL_MAX; i++)
	{
		UnloadTexture(g_LevelChooseTexture[i]);
	}

	UninitShop();
}


void UpdateLevelChoose()
{
	UpdateLevelChooseBG();
	
	/*if (GetControllerTrigger(NpadButton::L::Index))
	{
		//PlaySE(WSD_KETTEI);
		SetFade(FADEMODE_OUT);
		//SetVolumeBGM(0, 120);
	}*/
	if (GetControllerTrigger(NpadButton::A::Index))
	{
		for (int i = 0; i < LEVEL_MAX; i++)
		{
			if (isleveltouch && g_level[i].isChoose)
			{
				if (SetFade(FADEMODE_OUT))
				{
					PlaySE(WSD_SE_CLICK);
					isleveltouch = false;
					ShowUI(NOTHINGUI);
				}
			}
		}

	}
	if (GetControllerTrigger(NpadButton::B::Index))
	{
		for (int i = 0; i < LEVEL_MAX; i++)
		{
			if (isleveltouch && g_level[i].isChoose)
			{
				PlaySE(WSD_SE_UIMOVE);
				g_level[i].isChoose = false;
				isleveltouch = false;
				ShowUI(NOTHINGUI);
			}
		}

	}

	if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();

		for (int i = 0; i < LEVEL_MAX; i++)
		{
			if (GetIsTouch(touch, LEVELCHOOSESIZE / 2, LEVELCHOOSESIZE / 2, g_level[i].pos.x,g_level[i].pos.y) &&
				!isleveltouch &&
				g_level[i].isUnlock)
			{	
				PlaySE(WSD_SE_CLICK);
				g_level[i].isChoose = true;
				isleveltouch = true;

				ShowUI(LEVELCHOOSEUI);
				//PlaySE(WSD_KETTEI);
				
				//SetVolumeBGM(0, 120);
			}
			if (GetIsTouch(touch, XBTN_SIZE / 2, XBTN_SIZE / 2, LEVELXBTN_POSX, LEVELXBTN_POSY) &&
				isleveltouch &&
				g_level[i].isChoose)
			{
				PlaySE(WSD_SE_UIMOVE);
				g_level[i].isChoose = false;
				isleveltouch = false;
				ShowUI(NOTHINGUI);
			}

			if (GetIsTouch(touch, LEVELSTARTBTN_SIZEX, LEVELSTARTBTN_SIZEY, 0.0f, LEVELSTARTBTN_POSY) &&
				isleveltouch &&
				g_level[i].isChoose)
			{
				if (SetFade(FADEMODE_OUT))
				{
					PlaySE(WSD_SE_CLICK);
					isleveltouch = false;
					ShowUI(NOTHINGUI);
				}
			}
		}
		
	}

	UpdateShop();
	
}


void DrawLevelChoose()
{
	DrawLevelChooseBG();

	for (int i = 0; i < LEVEL_MAX; i++)
	{
		if (g_level[i].isUse)
		{
			SetTexture(g_LevelChooseTexture[g_level[i].levelnum]);

			if (g_level[i].isUnlock)
			{
				DrawSprite(g_level[i].pos.x, g_level[i].pos.y, g_level[i].size.x, g_level[i].size.y,
					0.0f, 0.0f, 1.0f, 1.0f,
					MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				DrawSprite(g_level[i].pos.x, g_level[i].pos.y, g_level[i].size.x, g_level[i].size.y,
					0.0f, 0.0f, 1.0f, 1.0f,
					MakeFloat4(0.4f, 0.4f, 0.4f, 1.0f));
			}
			
		}
	}

	DrawShop();
}

LEVEL* GetLevel(void)
{
	return g_level;
}

void SetLevel(Float2 pos, LEVELNUM levelnum)
{
	for (int i = 0; i < LEVEL_MAX; i++)
	{
		if (!g_level[i].isUse)
		{
			g_level[i].pos = pos;
			g_level[i].levelnum = levelnum;
			g_level[i].isUse = true;
			break;
		}
	}
}

bool GetIslevelTouch(void)
{
	return isleveltouch;
}

void SetIslevelTouch(bool ilt)
{
	isleveltouch = ilt;
}

void SetIsBossDefeted(LEVELNUM levelnum)
{
	g_level[levelnum].isBossDefeted = true;
}

void SetIsLevelUnlock(LEVELNUM levelnum)
{
	g_level[levelnum].isUnlock = true;
}
