#include "main.h"
#include "texture.h"
#include "sprite.h"

#include "progress.h"
#include "player.h"

unsigned int g_HPProgressTexture;
unsigned int g_shieldProgressTexture;
unsigned int g_progressTexture;

float g_HPPer;
float g_shieldPer;

void InitProgress()
{
	g_HPProgressTexture = LoadTexture("rom:/progress_fill_red.tga");
	g_shieldProgressTexture = LoadTexture("rom:/progress_fill_blue.tga");
	g_progressTexture = LoadTexture("rom:/progress_overlay.tga");
	g_HPPer = 1.0f;
	g_shieldPer = 1.0f;
}


void UninitProgress()
{
	UnloadTexture(g_HPProgressTexture);
	UnloadTexture(g_shieldProgressTexture);
	UnloadTexture(g_progressTexture);
}


void UpdateProgress()
{
	g_HPPer = float(GetPlayer().HP) / float(GetPlayer().maxHP);
	g_shieldPer = float(GetPlayer().shield) / float(GetPlayer().maxShield);
}


void DrawProgress()
{
	SetTexture(g_progressTexture);
	DrawSprite(HPPROGRESS_POSX, 0.0f,
		PROGRESS_SIZEX, SCREEN_HEIGHT / 2,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	
	SetTexture(g_HPProgressTexture);
	DrawSprite(HPPROGRESS_POSX, (SCREEN_HEIGHT / 2 * (1 - g_HPPer) / 2),
		PROGRESS_SIZEX, (SCREEN_HEIGHT / 2 * g_HPPer),
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	SetTexture(g_progressTexture);
	DrawSprite(SHIELDPROGRESS_POSX, 0.0f,
		PROGRESS_SIZEX, SCREEN_HEIGHT / 2,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	SetTexture(g_shieldProgressTexture);
	DrawSprite(SHIELDPROGRESS_POSX, (SCREEN_HEIGHT / 2 * (1 - g_shieldPer) / 2),
		PROGRESS_SIZEX, (SCREEN_HEIGHT / 2 * g_shieldPer),
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	
	
}
