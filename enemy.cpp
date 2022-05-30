//---------------------------------------------------------------
//enemy.cpp
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/07
//---------------------------------------------------------------
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "enemy.h"
#include "fade.h"
#include "enemybullet.h"
#include "player.h"

unsigned int g_EnemyTexture[ENEMY_TYPE_MAX];
ENEMY g_enemy[MAX_ENEMY];

void InitEnemy()
{
	g_EnemyTexture[LEVEL01_ENEMY_01] = LoadTexture("rom:/level01_enemy01.tga");
	g_EnemyTexture[LEVEL01_ENEMY_02] = LoadTexture("rom:/level01_enemy02.tga");
	g_EnemyTexture[LEVEL01_ENEMY_03] = LoadTexture("rom:/level01_enemy03.tga");
	g_EnemyTexture[LEVEL01_BOSS_01] = LoadTexture("rom:/level01_boss01.tga");
	g_EnemyTexture[LEVEL01_BOSS_02] = LoadTexture("rom:/level01_boss02.tga");
	g_EnemyTexture[LEVEL02_BOSS] = LoadTexture("rom:/level02_boss.tga");

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_enemy[i].pos = MakeFloat2(0.0f, 0.0f);
		g_enemy[i].vel = MakeFloat2(0.0f, 0.0f);
		g_enemy[i].size = MakeFloat2(0.0f, 0.0f);
		g_enemy[i].HP = 0;
		g_enemy[i].type - ENEMY_TYPE0;
		g_enemy[i].isUse = false;
		g_enemy[i].isChangeMode = false;
	}
	//SetEnemy(MakeFloat2(-340.0f, 0.0f), ENEMY_TYPE1);
	//SetEnemy(MakeFloat2(340.0f, 0.0f), ENEMY_TYPE1);
	//SetEnemy(MakeFloat2(-30.0f, -340.0f), ENEMY_TYPE1);
	//SetEnemy(MakeFloat2(30.0f, -340.0f), ENEMY_TYPE1);
	//SetEnemy(MakeFloat2(30.0f, -200.0f), ENEMY_TYPE2);
}

void UninitEnemy()
{
	for (int i = 0; i < ENEMY_TYPE_MAX; i++)
	{
		UnloadTexture(g_EnemyTexture[i]);
	}
}

void UpdateEnemy()
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_enemy[i].isUse)
		{
			g_enemy[i].pos.x += g_enemy[i].vel.x;
			g_enemy[i].pos.y += g_enemy[i].vel.y;
			g_enemy[i].shootTimer += 1;
			switch (g_enemy[i].type)
			{
			case LEVEL01_ENEMY_01:
			{
				if (g_enemy[i].shootTimer % 90 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x, g_enemy[i].pos.y + g_enemy[i].size.y / 2), MakeFloat2(0.0f, 10.0f), MakeFloat2(16.0f, 32.0f), ENEMYBULLET_TYPE1);
				}
				break;
			}
			case LEVEL01_ENEMY_02:
			{
				if (g_enemy[i].pos.x < (-SCREEN_WIDTH / 4) + g_enemy[i].size.x / 2)
				{
					g_enemy[i].vel.x *= -1;
				}
				if (g_enemy[i].pos.x > (SCREEN_WIDTH / 4) - g_enemy[i].size.x / 2)
				{
					g_enemy[i].vel.x *= -1;
				}
				if (g_enemy[i].shootTimer % 90 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + g_enemy[i].size.x / 2, g_enemy[i].pos.y), MakeFloat2(0.0f, 10.0f), MakeFloat2(16.0f, 32.0f), ENEMYBULLET_TYPE1);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - g_enemy[i].size.x / 2, g_enemy[i].pos.y), MakeFloat2(0.0f, 10.0f), MakeFloat2(16.0f, 32.0f), ENEMYBULLET_TYPE1);
				}
				break;
			}
			case LEVEL01_ENEMY_03:
			{
				if (g_enemy[i].pos.y > (-SCREEN_HEIGHT / 2) + g_enemy[i].size.y / 2 && !g_enemy[i].isChangeMode)
				{
					g_enemy[i].vel.y = 0.0f;
					g_enemy[i].vel.x = 1.0f;
					g_enemy[i].isChangeMode = true;
				}
				if (g_enemy[i].pos.x < (-SCREEN_WIDTH / 4) + g_enemy[i].size.x / 2)
				{
					g_enemy[i].vel.x *= -1;
				}
				if (g_enemy[i].pos.x > (SCREEN_WIDTH / 4) - g_enemy[i].size.x / 2)
				{
					g_enemy[i].vel.x *= -1;
				}
				if (g_enemy[i].shootTimer % 75 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x, g_enemy[i].pos.y + g_enemy[i].size.y / 2), MakeFloat2(0.0f, 15.0f), MakeFloat2(50.0f, 100.0f), ENEMYBULLET_TYPE2);
				}
				break;
			}	
			case LEVEL01_BOSS_01:
			{
				if (g_enemy[i].pos.y > (-SCREEN_HEIGHT / 2 + g_enemy[i].size.y / 2))
				{
					g_enemy[i].vel.y = 0;
				}
				g_enemy[i].shootRot += 3;
				if (g_enemy[i].shootTimer % 50 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + g_enemy[i].size.x / 2, g_enemy[i].pos.y + 100.0f), MakeFloat2(0.0f, 10.0f), MakeFloat2(16.0f, 32.0f), ENEMYBULLET_TYPE1);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - g_enemy[i].size.x / 2, g_enemy[i].pos.y + 100.0f), MakeFloat2(0.0f, 10.0f), MakeFloat2(16.0f, 32.0f), ENEMYBULLET_TYPE1);
				}
				if (g_enemy[i].shootTimer % (10 * FPS) > (5 * FPS) && g_enemy[i].shootTimer % (10 * FPS) < (10 * FPS - 1) && g_enemy[i].shootTimer % 8 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x, g_enemy[i].pos.y + LEVEL01_BOSS01_SIZEY / 2), MakeFloat2(8 * sin(g_enemy[i].shootRot), 8 * cos(g_enemy[i].shootRot)), MakeFloat2(32.0f, 32.0f), ENEMYBULLET_TYPE4);
					//SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 100.0f, g_enemy[i].pos.y + 50.0f), MakeFloat2(8 * cos(g_enemy[i].shootRot), 8 * sin(g_enemy[i].shootRot)), MakeFloat2(64.0f, 48.0f), BOSSBULLET_TYPE2);
				}
				break;
			}	
			case LEVEL01_BOSS_02:
			{
				if (g_enemy[i].pos.y > (-SCREEN_HEIGHT / 2 + g_enemy[i].size.y / 2 - 50.0f))
				{
					g_enemy[i].vel.y = 0;
				}
				g_enemy[i].shootRot += 3;
				if (!g_enemy[i].isChangeMode)
				{
					if (g_enemy[i].shootTimer % 120 == 0)
					{
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + 50.0f, g_enemy[i].pos.y + g_enemy[i].size.y / 2), MakeFloat2(0.0f, 10.0f), MakeFloat2(16.0f, 32.0f), ENEMYBULLET_TYPE1);
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 50.0f, g_enemy[i].pos.y + g_enemy[i].size.y / 2), MakeFloat2(0.0f, 10.0f), MakeFloat2(16.0f, 32.0f), ENEMYBULLET_TYPE1);
					}
					if (g_enemy[i].shootTimer % 150 == 0)
					{
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + g_enemy[i].size.x / 2, g_enemy[i].pos.y + 150.0f), MakeFloat2(0.0f, 15.0f), MakeFloat2(25.0f, 50.0f), ENEMYBULLET_TYPE3);
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - g_enemy[i].size.x / 2, g_enemy[i].pos.y + 150.0f), MakeFloat2(0.0f, 15.0f), MakeFloat2(25.0f, 50.0f), ENEMYBULLET_TYPE3);
					}
				}
				if (g_enemy[i].isChangeMode)
				{
					if (g_enemy[i].shootTimer % 90 == 0)
					{
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + 50.0f, g_enemy[i].pos.y + g_enemy[i].size.y / 2), MakeFloat2(0.0f, 10.0f), MakeFloat2(20.0f, 40.0f), ENEMYBULLET_TYPE1);
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 50.0f, g_enemy[i].pos.y + g_enemy[i].size.y / 2), MakeFloat2(0.0f, 10.0f), MakeFloat2(20.0f, 40.0f), ENEMYBULLET_TYPE1);
					}
					if (g_enemy[i].shootTimer % 150 == 0)
					{
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + g_enemy[i].size.x / 2, g_enemy[i].pos.y + 150.0f), MakeFloat2(0.0f, 15.0f), MakeFloat2(30.0f, 60.0f), ENEMYBULLET_TYPE2);
						SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - g_enemy[i].size.x / 2, g_enemy[i].pos.y + 150.0f), MakeFloat2(0.0f, 15.0f), MakeFloat2(30.0f, 60.0f), ENEMYBULLET_TYPE2);
					}
				}
				
				if (g_enemy[i].shootTimer % (15 * FPS) > (10 * FPS) && g_enemy[i].shootTimer % (10 * FPS) < (10 * FPS - 1) && g_enemy[i].shootTimer % 8 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x, g_enemy[i].pos.y + LEVEL01_BOSS01_SIZEY / 2), MakeFloat2(8 * sin(g_enemy[i].shootRot), 8 * cos(g_enemy[i].shootRot)), MakeFloat2(32.0f, 32.0f), ENEMYBULLET_TYPE4);
				}
				if (g_enemy[i].shield <= 0 && !g_enemy[i].isChangeMode)
				{
					g_enemy[i].isChangeMode = true;
				}
				if (g_enemy[i].shootTimer >= 6500 && g_enemy[i].shootTimer % 60 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x, g_enemy[i].pos.y), MakeFloat2(0.0f, 5.0f), MakeFloat2(960.0f, 128.0f), BOSSBULLET_TYPE3);
				}
				break;
			}	
			case LEVEL02_BOSS:
			{
				if (g_enemy[i].pos.y > -400.0f)
				{
					g_enemy[i].vel.y = 0.0f;
				}
				g_enemy[i].shootRot += 2;
				if (g_enemy[i].shootTimer % 80 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + 250.0f, g_enemy[i].pos.y + 250.0f), MakeFloat2(12.0f, 10.0f), MakeFloat2(32.0f, 48.0f), BOSSBULLET_TYPE1);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + 250.0f, g_enemy[i].pos.y + 250.0f), MakeFloat2(-12.0f, 10.0f), MakeFloat2(32.0f, 48.0f), BOSSBULLET_TYPE1);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + 250.0f, g_enemy[i].pos.y + 250.0f), MakeFloat2(0.0f, 10.0f), MakeFloat2(32.0f, 48.0f), BOSSBULLET_TYPE1);

					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 250.0f, g_enemy[i].pos.y + 250.0f), MakeFloat2(12.0f, 10.0f), MakeFloat2(32.0f, 48.0f), BOSSBULLET_TYPE1);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 250.0f, g_enemy[i].pos.y + 250.0f), MakeFloat2(0.0f, 10.0f), MakeFloat2(32.0f, 48.0f), BOSSBULLET_TYPE1);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 250.0f, g_enemy[i].pos.y + 250.0f), MakeFloat2(-12.0f, 10.0f), MakeFloat2(32.0f, 48.0f), BOSSBULLET_TYPE1);

					//g_shootSpeed = 0;
				}
				if (g_enemy[i].shield <= 0 && !g_enemy[i].isChangeMode)
				{
					g_enemy[i].shootTimer = 0;
					g_enemy[i].isChangeMode = true;
				}
				if (g_enemy[i].shootTimer % (10 * FPS) > (8 * FPS) && g_enemy[i].shootTimer % (10 * FPS) < (10 * FPS - 1) && g_enemy[i].shootTimer % 6 == 0)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + 100.0f, g_enemy[i].pos.y + 50.0f), MakeFloat2(8 * sin(g_enemy[i].shootRot), 8 * cos(g_enemy[i].shootRot)), MakeFloat2(64.0f, 48.0f), BOSSBULLET_TYPE2);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 100.0f, g_enemy[i].pos.y + 50.0f), MakeFloat2(8 * cos(g_enemy[i].shootRot), 8 * sin(g_enemy[i].shootRot)), MakeFloat2(64.0f, 48.0f), BOSSBULLET_TYPE2);
				}

				if (g_enemy[i].shootTimer % (7 * FPS) == 0 && g_enemy[i].isChangeMode)
				{
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x, g_enemy[i].pos.y + 250.0f), MakeFloat2(0.0f, 10.0f), MakeFloat2(175.0f, 175.0f), BOSSBULLET_TYPE3);
				}

				if (g_enemy[i].shootTimer % 90 == 0 && g_enemy[i].HP <= 30)
				{

					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x + 400.0f, g_enemy[i].pos.y + 50.0f), MakeFloat2(0.0f, 8.0f), MakeFloat2(64.0f, 64.0f), BOSSBULLET_TYPE4);
					SetEnemyBullet(MakeFloat2(g_enemy[i].pos.x - 400.0f, g_enemy[i].pos.y + 50.0f), MakeFloat2(0.0f, 8.0f), MakeFloat2(64.0f, 64.0f), BOSSBULLET_TYPE4);
				}
				break;
			}
			default:
				break;
			}

			PLAYER pPlayer = GetPlayer();
			if (pPlayer.pos.y + pPlayer.size.y / 2 > g_enemy[i].pos.y - g_enemy[i].size.y / 2 &&
				pPlayer.pos.y - pPlayer.size.y / 2 < g_enemy[i].pos.y + g_enemy[i].size.y / 2 &&
				pPlayer.pos.x + pPlayer.size.x / 2 > g_enemy[i].pos.x - g_enemy[i].size.x / 2 &&
				pPlayer.pos.x - pPlayer.size.x / 2 < g_enemy[i].pos.x + g_enemy[i].size.x / 2)
			{
				PlayerLifeDecrease(pPlayer.maxHP);			
			}
			
			//enemyCount += 1;
			if (g_enemy[i].pos.y >= (SCREEN_HEIGHT / 2 + g_enemy[i].size.y))
			{
				g_enemy[i].isUse = false;
			}
		}
	}
	
}

void DrawEnemy()
{
	

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_enemy[i].isUse)
		{
			SetTexture(g_EnemyTexture[g_enemy[i].type]);
			DrawSprite(g_enemy[i].pos.x, g_enemy[i].pos.y, g_enemy[i].size.x, g_enemy[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	
}

ENEMY* GetEnemy(void)
{
	return g_enemy;
}

void SetEnemy(Float2 pos, enemyType type)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!g_enemy[i].isUse)
		{
			g_enemy[i].pos = pos;
			/*g_enemy[i].vel = vel;
			g_enemy[i].size = size;*/
			g_enemy[i].type = type;
			g_enemy[i].shootRot = 0.0f;
			g_enemy[i].shootTimer = 0;
			g_enemy[i].isUse = true;
			g_enemy[i].isChangeMode = false;
			switch (g_enemy[i].type)
			{
			case LEVEL01_ENEMY_01:
				g_enemy[i].size = MakeFloat2(LEVEL01_ENEMY01_SIZEX, LEVEL01_ENEMY01_SIZEY);
				g_enemy[i].vel = MakeFloat2(0.0f, 2.0f);
				g_enemy[i].HP = 1;
				g_enemy[i].shield = 2;
				g_enemy[i].score = 200;
				break;
			case LEVEL01_ENEMY_02:
				g_enemy[i].size = MakeFloat2(LEVEL01_ENEMY02_SIZEX, LEVEL01_ENEMY02_SIZEY);
				g_enemy[i].vel = MakeFloat2(4.0f, 1.5f);
				g_enemy[i].HP = 2;
				g_enemy[i].shield = 4;
				g_enemy[i].score = 400;
				break;
			case LEVEL01_ENEMY_03:
				g_enemy[i].size = MakeFloat2(LEVEL01_ENEMY03_SIZEX, LEVEL01_ENEMY03_SIZEY);
				g_enemy[i].vel = MakeFloat2(0.0f, 1.0f);
				g_enemy[i].HP = 4;
				g_enemy[i].shield = 7;
				g_enemy[i].score = 800;
				break;
			case LEVEL01_BOSS_01:
				g_enemy[i].size = MakeFloat2(LEVEL01_BOSS01_SIZEX, LEVEL01_BOSS01_SIZEY);
				g_enemy[i].vel = MakeFloat2(0.0f, 3.0f);
				g_enemy[i].HP = 20;
				g_enemy[i].shield = 30;
				g_enemy[i].score = 2000;
				break;
			case LEVEL01_BOSS_02:
				g_enemy[i].size = MakeFloat2(LEVEL01_BOSS02_SIZEX, LEVEL01_BOSS02_SIZEY);
				g_enemy[i].vel = MakeFloat2(0.0f, 1.5f);
				g_enemy[i].HP = 50;
				g_enemy[i].shield = 100;
				g_enemy[i].score = 5000;
				break;
			case LEVEL02_BOSS:
				g_enemy[i].size = MakeFloat2(LEVEL02_BOSS_SIZEX, LEVEL02_BOSS_SIZEY);
				g_enemy[i].vel = MakeFloat2(0.0f, 1.0f);
				g_enemy[i].HP = 100;
				g_enemy[i].shield = 200;
				g_enemy[i].score = 10000;
				break;
			default:
				break;
			}

			break;
		}
	}
}


