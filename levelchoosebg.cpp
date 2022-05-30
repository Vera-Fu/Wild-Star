#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "levelchoosebg.h"


unsigned int g_LevelChooseBGTexture;


void InitLevelChooseBG()
{
	g_LevelChooseBGTexture = LoadTexture("rom:/levelchoosebg.tga");
}


void UninitLevelChooseBG()
{
	UnloadTexture(g_LevelChooseBGTexture);
}


void UpdateLevelChooseBG()
{

}


void DrawLevelChooseBG()
{
	SetTexture(g_LevelChooseBGTexture);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}