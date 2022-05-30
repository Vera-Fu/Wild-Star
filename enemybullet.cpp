//---------------------------------------------------------------
//enemybullet.cpp
//
//												作成者：FU YIZHI
//												作成日：2021/6/28
//---------------------------------------------------------------

#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"
#include "explosion.h"
#include "enemybullet.h"
#include "enemy.h"
#include "player.h"
#include "explosion.h"
#include <math.h>

unsigned int	g_EnemyBulletTexture[ENEMYBULLET_TYPE_MAX];

ENEMYBULLET g_enemybullet[MAX_ENEMYBULLET];	//実態

//int g_shootSpeed = 0;
//float g_rot = 0.0f;

void InitEnemyBullet()
{

	g_EnemyBulletTexture[ENEMYBULLET_TYPE1] = LoadTexture("rom:/enemybullet_01.tga");
	g_EnemyBulletTexture[ENEMYBULLET_TYPE2] = LoadTexture("rom:/enemybullet_02.tga");
	g_EnemyBulletTexture[ENEMYBULLET_TYPE3] = LoadTexture("rom:/enemybullet_03.tga");
	g_EnemyBulletTexture[ENEMYBULLET_TYPE4] = LoadTexture("rom:/enemybullet_04.tga");
	g_EnemyBulletTexture[BOSSBULLET_TYPE1] = LoadTexture("rom:/bossbullet_01.tga");
	g_EnemyBulletTexture[BOSSBULLET_TYPE2] = LoadTexture("rom:/bossbullet_02.tga");
	g_EnemyBulletTexture[BOSSBULLET_TYPE3] = LoadTexture("rom:/bossbullet_03.tga");
	g_EnemyBulletTexture[BOSSBULLET_TYPE4] = LoadTexture("rom:/bossbullet_04.tga");


	for (int enemybulletCnt = 0; enemybulletCnt < MAX_ENEMYBULLET; enemybulletCnt++)
	{
		g_enemybullet[enemybulletCnt].pos = MakeFloat2(0.0f, 0.0f);
		g_enemybullet[enemybulletCnt].vel = MakeFloat2(0.0f, 0.0f);
		g_enemybullet[enemybulletCnt].size = MakeFloat2(0.0f, 0.0f);
		g_enemybullet[enemybulletCnt].type = ENEMYBULLET_TYPE0;
		g_enemybullet[enemybulletCnt].damage = 0;
		g_enemybullet[enemybulletCnt].isShieldIgnore = false;
		g_enemybullet[enemybulletCnt].isUse = false;
	}
}



void UninitEnemyBullet()
{
	//テクスチャの解放
	for (int i = 0; i < ENEMYBULLET_TYPE_MAX; i++)
	{
		UnloadTexture(g_EnemyBulletTexture[i]);
	}

}


void UpdateEnemyBullet()
{
	/*g_rot += 2;
	if (g_shootSpeed < ENEMYSHOOTSPEED)
	{
		
		g_shootSpeed++;
	}
	else
	{
		ENEMY* pEnemy = GetEnemy();
		for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
		{
			if ((pEnemy + enemyCnt)->isUse)
			{
				SetEnemyBullet((pEnemy + enemyCnt)->pos, MakeFloat2(10 * sin(g_rot), 10 * cos(g_rot)), MakeFloat2(48.0f, 48.0f), ENEMYBULLET_TYPE1);
				SetEnemyBullet((pEnemy + enemyCnt)->pos, MakeFloat2(10 * cos(g_rot), 10 * sin(g_rot)), MakeFloat2(48.0f, 48.0f), ENEMYBULLET_TYPE1);
			}
		}
		g_shootSpeed = 0;
	}*/
	for (int enemybulletCnt = 0; enemybulletCnt < MAX_ENEMYBULLET; enemybulletCnt++)
	{
		if (g_enemybullet[enemybulletCnt].isUse)
		{
			//ここから更新処理を書く
			//g_enemybullet[i].vel.y = 20.0f;
			g_enemybullet[enemybulletCnt].pos.x += g_enemybullet[enemybulletCnt].vel.x;
			g_enemybullet[enemybulletCnt].pos.y += g_enemybullet[enemybulletCnt].vel.y;

			PLAYER pPlayer = GetPlayer();
			if (pPlayer.pos.y + pPlayer.size.y / 2 > g_enemybullet[enemybulletCnt].pos.y - g_enemybullet[enemybulletCnt].size.y / 2 &&
				pPlayer.pos.y - pPlayer.size.y / 2 < g_enemybullet[enemybulletCnt].pos.y + g_enemybullet[enemybulletCnt].size.y / 2 &&
				pPlayer.pos.x + pPlayer.size.x / 2 > g_enemybullet[enemybulletCnt].pos.x - g_enemybullet[enemybulletCnt].size.x / 2 &&
				pPlayer.pos.x - pPlayer.size.x / 2 < g_enemybullet[enemybulletCnt].pos.x + g_enemybullet[enemybulletCnt].size.x / 2)
			{
				//弾を消す
				g_enemybullet[enemybulletCnt].isUse = false;
				SetControllerLeftVibration(1);
				SetControllerRightVibration(1);
				if (!g_enemybullet[enemybulletCnt].isShieldIgnore)
				{
					if (pPlayer.shield > 0)
					{
						PlayerShieldDecrease(g_enemybullet[enemybulletCnt].damage);
					}
					else
					{
						PlayerLifeDecrease(g_enemybullet[enemybulletCnt].damage);				
					}
				}
				else
				{
					PlayerLifeDecrease(g_enemybullet[enemybulletCnt].damage);
				}
				//爆発セット
				//SetExplosion(pPlayer.pos, pPlayer.size);
			}

			//上壁に当たったら消える
			if (g_enemybullet[enemybulletCnt].pos.y <= -(SCREEN_HEIGHT / 2) ||
				g_enemybullet[enemybulletCnt].pos.y >= (SCREEN_HEIGHT / 2)  ||
				g_enemybullet[enemybulletCnt].pos.x <= (-SCREEN_WIDTH / 4)  ||
				g_enemybullet[enemybulletCnt].pos.x >= (SCREEN_WIDTH / 4))
			{
				
				g_enemybullet[enemybulletCnt].isUse = false;
			}
		}
	}
}


void DrawEnemyBullet()
{
	for (int enemybulletCnt = 0; enemybulletCnt < MAX_ENEMYBULLET; enemybulletCnt++)
	{
		if (g_enemybullet[enemybulletCnt].isUse)
		{
			SetTexture(g_EnemyBulletTexture[g_enemybullet[enemybulletCnt].type]);

			DrawSprite(g_enemybullet[enemybulletCnt].pos.x, g_enemybullet[enemybulletCnt].pos.y, g_enemybullet[enemybulletCnt].size.x, g_enemybullet[enemybulletCnt].size.y,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		}
	}

}

ENEMYBULLET* GetEnemyBullet(void)
{
	return g_enemybullet;
}

void SetEnemyBullet(Float2 pos, Float2 vel, Float2 size, enemybulletType type)
{
	for (int enemybulletCnt = 0; enemybulletCnt < MAX_ENEMYBULLET; enemybulletCnt++)
	{
		if (!g_enemybullet[enemybulletCnt].isUse)
		{
			g_enemybullet[enemybulletCnt].pos = pos;
			g_enemybullet[enemybulletCnt].vel = vel;
			g_enemybullet[enemybulletCnt].size = size;
			g_enemybullet[enemybulletCnt].type = type;
			g_enemybullet[enemybulletCnt].isUse = true;
			switch (g_enemybullet[enemybulletCnt].type)
			{
			case ENEMYBULLET_TYPE1:
				g_enemybullet[enemybulletCnt].damage = 1;
				g_enemybullet[enemybulletCnt].isShieldIgnore = false;
				break;
			case ENEMYBULLET_TYPE2:
				g_enemybullet[enemybulletCnt].damage = 2;
				g_enemybullet[enemybulletCnt].isShieldIgnore = true;
				break;
			case ENEMYBULLET_TYPE3:
				g_enemybullet[enemybulletCnt].damage = 1;
				g_enemybullet[enemybulletCnt].isShieldIgnore = true;
				break;
			case ENEMYBULLET_TYPE4:
				g_enemybullet[enemybulletCnt].damage = 2;
				g_enemybullet[enemybulletCnt].isShieldIgnore = false;
				break;
			case BOSSBULLET_TYPE1:
				g_enemybullet[enemybulletCnt].damage = 1;
				g_enemybullet[enemybulletCnt].isShieldIgnore = false;
				break;
			case BOSSBULLET_TYPE2:
				g_enemybullet[enemybulletCnt].damage = 2;
				g_enemybullet[enemybulletCnt].isShieldIgnore = false;
				break;
			case BOSSBULLET_TYPE3:
				g_enemybullet[enemybulletCnt].damage = 2;
				g_enemybullet[enemybulletCnt].isShieldIgnore = true;
				break;
			case BOSSBULLET_TYPE4:
				g_enemybullet[enemybulletCnt].damage = 1;
				g_enemybullet[enemybulletCnt].isShieldIgnore = true;
				break;
			default:
				break;
			}

			break;
		}
	}
}
