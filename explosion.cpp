//---------------------------------------------------------------
//explosion.cpp
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/14
//---------------------------------------------------------------
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "explosion.h"
#include "sound.h"

unsigned int g_ExplosionTexture[EXPLOSION_TYPE_MAX];
EXPLOSION g_explosion[MAX_EXPLOSION];

void InitExplosion()
{
	g_ExplosionTexture[EXPLOSION_TYPE1] = LoadTexture("rom:/explosion_01.tga");
	g_ExplosionTexture[EXPLOSION_TYPE2] = LoadTexture("rom:/explosion_02.tga");
	g_ExplosionTexture[EXPLOSION_TYPE3] = LoadTexture("rom:/explosion_03.tga");
	g_ExplosionTexture[EXPLOSION_TYPE4] = LoadTexture("rom:/explosion_04.tga");

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		g_explosion[i].pos = MakeFloat2(0.0f, 0.0f);
		g_explosion[i].size = MakeFloat2(0.0f, 0.0f);
		g_explosion[i].isUse = false;
		g_explosion[i].frame = 0;
	}
}

void UninitExplosion()
{
	for (int i = 0; i < EXPLOSION_TYPE_MAX; i++)
	{
		UnloadTexture(g_ExplosionTexture[i]);
	}
	
}

void UpdateExplosion()
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (g_explosion[i].isUse)
		{
			g_explosion[i].frame++;
			if (g_explosion[i].frame >= 64)
			{
				g_explosion[i].isUse = false;
			}
		}
	}
}

void DrawExplosion()
{
	

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (g_explosion[i].isUse)
		{
			SetTexture(g_ExplosionTexture[g_explosion[i].type]);
			DrawSprite(g_explosion[i].pos.x, g_explosion[i].pos.y, g_explosion[i].size.x, g_explosion[i].size.y,
				g_explosion[i].frame % 8 * 0.125f, 
				g_explosion[i].frame / 8 * 0.125f, 
				0.125f, 
				0.125f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));	
		}
	}

}

EXPLOSION* GetExplosion(void)
{
	return g_explosion;
}

void SetExplosion(Float2 pos, Float2 size, EXPLOSIONTYPE type)
{
	switch (type)
	{
	case EXPLOSION_TYPE1:
		PlaySE(WSD_SE_EXPLOSION1);
		break;
	case EXPLOSION_TYPE2:
		PlaySE(WSD_SE_EXPLOSION2);
		break;
	case EXPLOSION_TYPE3:
		PlaySE(WSD_SE_EXPLOSION3);
		break;
	case EXPLOSION_TYPE4:
		PlaySE(WSD_SE_EXPLOSION4);
		break;
	default:
		break;
	}
	SetControllerLeftVibration(2);
	SetControllerRightVibration(2);
	
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (!g_explosion[i].isUse)
		{
			g_explosion[i].pos = pos;
			g_explosion[i].size = size;
			g_explosion[i].type = type;
			g_explosion[i].frame = 0;
			g_explosion[i].isUse = true;

			break;
		}
	}
}