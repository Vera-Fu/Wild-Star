#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "fade.h"

#include "levelbg.h"
#include "levelchoose.h"
#include "UI.h"
#include "sound.h"

unsigned int g_LevelBGTexture[LEVEL_MAX];
unsigned int g_MenuBTNTexture;

float bgposy;
bool isMenuBTNtouch;

BATTLEMENUBTN g_battlemenubtn;

void InitLevelBG()
{
	ShowUI(NOTHINGUI);
	g_LevelBGTexture[LEVEL_01] = LoadTexture("rom:/levelbg_01.tga");
	g_LevelBGTexture[LEVEL_02] = LoadTexture("rom:/levelbg_02.tga");
	g_LevelBGTexture[LEVEL_03] = LoadTexture("rom:/levelbg_03.tga");
	g_LevelBGTexture[LEVEL_04] = LoadTexture("rom:/levelbg_04.tga");

	g_MenuBTNTexture = LoadTexture("rom:/MENU_button.tga");


	bgposy = 0.0f;
	isMenuBTNtouch = false;
	g_battlemenubtn = BTN_CONTINUE;
}


void UninitLevelBG()
{
	for (int i = 0; i < LEVEL_MAX; i++)
	{
		UnloadTexture(g_LevelBGTexture[i]);
	}
	UnloadTexture(g_MenuBTNTexture);
	
}


void UpdateLevelBG()
{
	bgposy += ROLL_SPD;
	if (bgposy >= SCREEN_HEIGHT * 2)
	{
		bgposy = 0.0f;
	}
	if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();

		if (GetIsTouch(touch, MENUBTN_SIZE / 2, MENUBTN_SIZE / 2, MENUBTN_POSX, MENUBTN_POSY) &&
			!isMenuBTNtouch)
		{
			PlaySE(WSD_SE_CLICK);
			isMenuBTNtouch = true;
			ShowUI(BATTLEMENUUI);
		}
		if (GetIsTouch(touch, XBTN_SIZE / 2, XBTN_SIZE / 2, SHOPXBTN_POSX, SHOPXBTN_POSY) &&
			isMenuBTNtouch)
		{
			PlaySE(WSD_SE_UIMOVE);
			isMenuBTNtouch = false;
			ShowUI(NOTHINGUI);
		}
	}
	if (GetControllerTrigger(NpadButton::X::Index) && !isMenuBTNtouch)
	{
		PlaySE(WSD_SE_CLICK);
		isMenuBTNtouch = true;
		ShowUI(BATTLEMENUUI);
	}
	if (isMenuBTNtouch)
	{
		if (GetControllerTouchScreen())
		{
			Float2 touch;
			touch = GetControllerTouchScreenPosition();
			if (GetIsTouch(touch, BATTLEMENUBTN_SIZEX / 2, BATTLEMENUBTN_SIZEY / 2, 0.0f, BATTLEMENUCONTINUEBTN_POSY))
			{
				PlaySE(WSD_SE_CLICK);
				g_battlemenubtn = BTN_CONTINUE;
				ShowUI(NOTHINGUI);
				isMenuBTNtouch = false;
			}
			if (GetIsTouch(touch, BATTLEMENUBTN_SIZEX / 2, BATTLEMENUBTN_SIZEY / 2, 0.0f, BATTLEMENUQUITBTN_POSY))
			{
				PlaySE(WSD_SE_CLICK);
				g_battlemenubtn = BTN_BATTLEQUIT;
				SetFade(FADEMODE_OUT);
				isMenuBTNtouch = false;
			}
		}	
		if (GetControllerTrigger(NpadButton::Down::Index) ||
			GetControllerTrigger(NpadButton::Up::Index) ||
			GetControllerTrigger(NpadButton::StickLDown::Index) ||
			GetControllerTrigger(NpadButton::StickLUp::Index))
		{
			PlaySE(WSD_SE_UIMOVE);
			switch (g_battlemenubtn)
			{
			case BTN_CONTINUE:
				g_battlemenubtn = BTN_BATTLEQUIT;
				break;
			case BTN_BATTLEQUIT:
				g_battlemenubtn = BTN_CONTINUE;
				break;
			default:
				break;
			}
		}
		if (GetControllerTrigger(NpadButton::A::Index))
		{
			PlaySE(WSD_SE_CLICK);
			switch (GetBMBTN())
			{
			case BTN_CONTINUE:
				ShowUI(NOTHINGUI);
				isMenuBTNtouch = false;
				break;
			case BTN_BATTLEQUIT:
				SetFade(FADEMODE_OUT);
				isMenuBTNtouch = false;
				break;
			default:
				break;
			}
		}
		if (GetControllerTrigger(NpadButton::B::Index))
		{
			PlaySE(WSD_SE_UIMOVE);
			g_battlemenubtn = BTN_CONTINUE;
			ShowUI(NOTHINGUI);
			isMenuBTNtouch = false;
		}
	}
	
}


void DrawLevelBG()
{
	for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
	{
		if ((GetLevel() + levelNum)->isChoose)
		{
			SetTexture(g_LevelBGTexture[(GetLevel() + levelNum)->levelnum]);
		}
	}

	DrawSprite(0.0f, bgposy, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(0.0f, bgposy - SCREEN_HEIGHT * 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	SetTexture(g_MenuBTNTexture);
	DrawSprite(MENUBTN_POSX, MENUBTN_POSY, MENUBTN_SIZE, MENUBTN_SIZE,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}

BATTLEMENUBTN GetBMBTN(void)
{
	return g_battlemenubtn;
}
