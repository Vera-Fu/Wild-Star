
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "gamebg.h"


unsigned int g_GameBGTexture;

//float bgposy;

void InitGameBG()
{
	g_GameBGTexture = LoadTexture("rom:/gamebg1.tga");
	//bgposy = 0.0f;
}


void UninitGameBG()
{
	UnloadTexture(g_GameBGTexture);
}


void UpdateGameBG()
{
	//bgposy += ROLL_SPD;
	/*if (bgposy >= SCREEN_HEIGHT)
	{
		bgposy = 0.0f;
	}*/
}


void DrawGameBG()
{
	/*SetTexture(g_GameBGTexture);

	DrawSprite(0.0f, bgposy, SCREEN_WIDTH / 2, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSprite(0.0f, bgposy - SCREEN_HEIGHT, SCREEN_WIDTH / 2, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));*/

}
