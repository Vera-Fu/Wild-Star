//---------------------------------------------------------------
//titlebg.cpp
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/25
//---------------------------------------------------------------

#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "title.h"
#include "titlebg.h"
#include "UI.h"


unsigned int g_TitleBGTexture;
unsigned int g_StartBTNDownTexture;
unsigned int g_StartBTNUpTexture;
unsigned int g_QuitBTNDownTexture;
unsigned int g_QuitBTNUpTexture;
//unsigned int g_ChangeSceneTITexture;


void InitTitleBG()
{
	ShowUI(NOTHINGUI);
	g_TitleBGTexture = LoadTexture("rom:/titlebg.tga");
	g_StartBTNDownTexture = LoadTexture("rom:/START_buttondown.tga");
	g_StartBTNUpTexture = LoadTexture("rom:/START_buttonup.tga");
	g_QuitBTNDownTexture = LoadTexture("rom:/QUIT_buttondown.tga");
	g_QuitBTNUpTexture = LoadTexture("rom:/QUIT_buttonup.tga");
	//g_ChangeSceneTITexture = LoadTexture("rom:/changescene.tga");
}


void UninitTitleBG()
{
	UnloadTexture(g_TitleBGTexture);
	UnloadTexture(g_StartBTNDownTexture);
	UnloadTexture(g_StartBTNUpTexture);
	UnloadTexture(g_QuitBTNDownTexture);
	UnloadTexture(g_QuitBTNUpTexture);
}


void UpdateTitleBG()
{
	
}


void DrawTitleBG()
{
	SetTexture(g_TitleBGTexture);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	switch (GetBTN())
	{
	case BTN_START:
		SetTexture(g_StartBTNDownTexture);

		DrawSprite(0.0f, START_BTN_POSY, TITLE_BTN_SIZE_X, TITLE_BTN_SIZE_Y,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_QuitBTNUpTexture);

		DrawSprite(0.0f, QUIT_BTN_POSY, TITLE_BTN_SIZE_X, TITLE_BTN_SIZE_Y,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case BTN_QUIT:
		SetTexture(g_StartBTNUpTexture);

		DrawSprite(0.0f, START_BTN_POSY, TITLE_BTN_SIZE_X, TITLE_BTN_SIZE_Y,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_QuitBTNDownTexture);

		DrawSprite(0.0f, QUIT_BTN_POSY, TITLE_BTN_SIZE_X, TITLE_BTN_SIZE_Y,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
	
	/*
	SetTexture(g_ChangeSceneTITexture);

	DrawSprite(0.0f, 300.0f, 500.0f, 400.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	*/

}