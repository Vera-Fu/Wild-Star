//---------------------------------------------------------------
//title.cpp
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/25
//---------------------------------------------------------------

#include "main.h"
#include "title.h"
#include "titlebg.h"
#include "fade.h"
#include "controller.h"
#include "sound.h"

bool istouch;
TITLEBTN g_titlebtn;
unsigned int titleBgm;

void InitTitle()
{
	InitTitleBG();
	PlayBGM(STRM_BGM_TITLE);
	istouch = false;
	g_titlebtn = BTN_START;
}


void UninitTitle()
{
	UninitTitleBG();
	StopBGM();
}


void UpdateTitle()
{
	UpdateTitleBG();
	/*if (GetControllerTrigger(NpadButton::L::Index))
	{
		//PlaySE(WSD_KETTEI);
		SetFade(FADEMODE_OUT);
		//SetVolumeBGM(0, 120);
	}*/
	if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();
		if (GetIsTouch(touch, TITLE_BTN_SIZE_X, TITLE_BTN_SIZE_Y, 0.0f, START_BTN_POSY) && !istouch)
		{	
			g_titlebtn = BTN_START;
			if (SetFade(FADEMODE_OUT))
			{
				istouch = true;
				PlaySE(WSD_SE_CLICK);
			}
		}
		if (GetIsTouch(touch, TITLE_BTN_SIZE_X, TITLE_BTN_SIZE_Y, 0.0f, QUIT_BTN_POSY) && !istouch)
		{
			g_titlebtn = BTN_QUIT;
			PlaySE(WSD_SE_CLICK);
			istouch = true;
			SetUninit();
		}
	}

	if (GetControllerTrigger(NpadButton::Down::Index)		||
		GetControllerTrigger(NpadButton::Up::Index)			||
		GetControllerTrigger(NpadButton::StickLDown::Index)   ||
		GetControllerTrigger(NpadButton::StickLUp::Index))
	{
		switch (g_titlebtn)
		{
		case BTN_START:
			PlaySE(WSD_SE_UIMOVE);
			g_titlebtn = BTN_QUIT;
			break;
		case BTN_QUIT:
			PlaySE(WSD_SE_UIMOVE);
			g_titlebtn = BTN_START;
			break;
		default:
			break;
		}
	}

	if (GetControllerTrigger(NpadButton::A::Index))
	{
		switch (g_titlebtn)
		{
		case BTN_START:
			PlaySE(WSD_SE_CLICK);
			SetFade(FADEMODE_OUT);
			break;
		case BTN_QUIT:
			PlaySE(WSD_SE_CLICK);
			SetUninit();
			break;
		default:
			break;
		}
	}
}


void DrawTitle()
{
	DrawTitleBG();
}

TITLEBTN GetBTN(void)
{
	return g_titlebtn;
}
