//---------------------------------------------------------------
//bullet.cpp
//
//												作成者：FU YIZHI
//												作成日：2021/5/31
//---------------------------------------------------------------

#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "player.h"
#include "levelchoose.h"
#include "fade.h"
#include "sound.h"

unsigned int g_BulletTexture[BULLET_TYPE_MAX];
unsigned int g_BulletUseTexture[BULLET_USE_MAX];
unsigned int g_BulletNumTexture;

BULLET g_bullet[MAX_BULLET];	//実態

void InitBullet()
{
	g_BulletTexture[BULLET_TYPE1] = LoadTexture("rom:/bullet_01.tga");
	g_BulletTexture[BULLET_TYPE2] = LoadTexture("rom:/bullet_02.tga");
	g_BulletTexture[BULLET_TYPE3] = LoadTexture("rom:/bullet_03.tga");
	g_BulletUseTexture[BULLET_USE_02] = LoadTexture("rom:/bulletuse_02.tga");
	g_BulletUseTexture[BULLET_USE_03] = LoadTexture("rom:/bulletuse_03.tga");
	g_BulletNumTexture = LoadTexture("rom:/number.tga");

	for (int bulletCnt = 0; bulletCnt < MAX_BULLET; bulletCnt++)
	{
		g_bullet[bulletCnt].pos = MakeFloat2(0.0f, 0.0f);
		g_bullet[bulletCnt].vel = MakeFloat2(0.0f, 0.0f);
		g_bullet[bulletCnt].size = MakeFloat2(0.0f, 0.0f);
		g_bullet[bulletCnt].type = BULLET_TYPE0;
		g_bullet[bulletCnt].isUse = false;
	}
}



void UninitBullet()
{
	//テクスチャの解放
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		UnloadTexture(g_BulletTexture[i]);
	}
	for (int i = 0; i < BULLET_USE_MAX; i++)
	{
		UnloadTexture(g_BulletUseTexture[i]);
	}
	UnloadTexture(g_BulletNumTexture);
}


void UpdateBullet()
{
	for (int bulletCnt = 0; bulletCnt < MAX_BULLET; bulletCnt++)
	{
		if (g_bullet[bulletCnt].isUse)
		{
			//ここから更新処理を書く
			//g_bullet[i].vel.y = 20.0f;
			g_bullet[bulletCnt].pos.x += g_bullet[bulletCnt].vel.x;
			g_bullet[bulletCnt].pos.y += g_bullet[bulletCnt].vel.y;

			//当たり判定
			//ENEMY* GetEnemy() = GetEnemy();
			for (int enemyCnt = 0; enemyCnt < MAX_ENEMY; enemyCnt++)
			{
				if ((GetEnemy() + enemyCnt)->isUse)
				{
					if ((GetEnemy() + enemyCnt)->pos.y + (GetEnemy() + enemyCnt)->size.y / 2 > g_bullet[bulletCnt].pos.y - g_bullet[bulletCnt].size.y / 2 &&
						(GetEnemy() + enemyCnt)->pos.y - (GetEnemy() + enemyCnt)->size.y / 2 < g_bullet[bulletCnt].pos.y + g_bullet[bulletCnt].size.y / 2 &&
						(GetEnemy() + enemyCnt)->pos.x + (GetEnemy() + enemyCnt)->size.x / 2 > g_bullet[bulletCnt].pos.x - g_bullet[bulletCnt].size.x / 2 &&
						(GetEnemy() + enemyCnt)->pos.x - (GetEnemy() + enemyCnt)->size.x / 2 < g_bullet[bulletCnt].pos.x + g_bullet[bulletCnt].size.x / 2)
					{
						//弾を消す
						g_bullet[bulletCnt].isUse = false;

						//敵を消す
						if (!g_bullet[bulletCnt].isShieldIgnore)
						{
							if ((GetEnemy() + enemyCnt)->shield > 0)
							{
								(GetEnemy() + enemyCnt)->shield -= g_bullet[bulletCnt].damage;
							}
							else
							{
								(GetEnemy() + enemyCnt)->HP -= g_bullet[bulletCnt].damage;
							}
						}
						else
						{
							(GetEnemy() + enemyCnt)->HP -= g_bullet[bulletCnt].damage;
						}

						if ((GetEnemy() + enemyCnt)->HP <= 0)
						{
							(GetEnemy() + enemyCnt)->isUse = false;

							//爆発セット
							if ((GetEnemy() + enemyCnt)->type < LEVEL01_BOSS_01)
							{
								SetExplosion((GetEnemy() + enemyCnt)->pos, MakeFloat2((GetEnemy() + enemyCnt)->size.x * 2, (GetEnemy() + enemyCnt)->size.y * 2), EXPLOSION_TYPE1);
							}
							if ((GetEnemy() + enemyCnt)->type == LEVEL01_BOSS_01 || (GetEnemy() + enemyCnt)->type == LEVEL01_BOSS_02)
							{
								SetExplosion((GetEnemy() + enemyCnt)->pos, (GetEnemy() + enemyCnt)->size, EXPLOSION_TYPE2);
							}
							if ((GetEnemy() + enemyCnt)->type == LEVEL02_BOSS)
							{
								SetExplosion((GetEnemy() + enemyCnt)->pos, (GetEnemy() + enemyCnt)->size, EXPLOSION_TYPE3);
							}
							
							AddScore((GetEnemy() + enemyCnt)->score);

							if ((GetEnemy() + enemyCnt)->type == LEVEL01_BOSS_02 && (GetLevel() + LEVEL_01)->isChoose)
							{
								PlaySE(WSD_SE_VICTORY);
								SetIsBossDefeted(LEVEL_01);
								SetIsLevelUnlock(LEVEL_02);
								SetFade(FADEMODE_OUT);
							}
							if ((GetEnemy() + enemyCnt)->type == LEVEL02_BOSS && (GetLevel() + LEVEL_02)->isChoose)
							{
								PlaySE(WSD_SE_VICTORY);
								SetIsBossDefeted(LEVEL_02);
								SetIsLevelUnlock(LEVEL_03);
								SetFade(FADEMODE_OUT);
							}
							if ((GetEnemy() + enemyCnt)->type == LEVEL02_BOSS && (GetLevel() + LEVEL_03)->isChoose)
							{
								PlaySE(WSD_SE_VICTORY);
								SetIsBossDefeted(LEVEL_03);
								SetIsLevelUnlock(LEVEL_04);
								SetFade(FADEMODE_OUT);
							}
							if ((GetEnemy() + enemyCnt)->type == LEVEL02_BOSS && (GetLevel() + LEVEL_04)->isChoose)
							{
								PlaySE(WSD_SE_VICTORY);
								SetIsBossDefeted(LEVEL_04);
								SetFade(FADEMODE_OUT);
							}
						}
						break;
					}
				}
			}

			//上壁に当たったら消える
			if (g_bullet[bulletCnt].pos.y <= (-SCREEN_HEIGHT / 2) ||
				g_bullet[bulletCnt].pos.y >= (SCREEN_HEIGHT / 2)  ||
				g_bullet[bulletCnt].pos.x <= (-SCREEN_WIDTH / 4)  ||
				g_bullet[bulletCnt].pos.x >= (SCREEN_WIDTH / 4))
			{
				g_bullet[bulletCnt].isUse = false;
			}
		}
	}
	
}


void DrawBullet()
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].isUse)
		{
			SetTexture(g_BulletTexture[g_bullet[i].type]);

			DrawSprite(g_bullet[i].pos.x, g_bullet[i].pos.y, g_bullet[i].size.x, g_bullet[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		}
	}
	SetTexture(g_BulletUseTexture[BULLET_USE_02]);
	DrawSprite(BULLETUSE_POSX, BULLETUSE_02_POSY, BULLETUSE_SIZE, BULLETUSE_SIZE,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	SetTexture(g_BulletUseTexture[BULLET_USE_03]);
	DrawSprite(BULLETUSE_POSX, BULLETUSE_03_POSY, BULLETUSE_SIZE, BULLETUSE_SIZE,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	SetTexture(g_BulletNumTexture);

	int bullet02Num = GetPlayer().bullet02Num;
	for (int i = 0; i < BULLETUSE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = bullet02Num % 10;			//下一桁だけ抽出

		//テクスチャ座標始点を計算
		tx = (n % 5) * 0.2f;
		ty = (n / 5) * 0.2f;

		bullet02Num /= 10;			//桁を一つ右にずらす

		float sx, sy;
		sx = BULLETUSE_POSX + 150.0f + 30.0f * (BULLETUSE_FIGURE - 1 - i);
		sy = BULLETUSE_02_POSY;

		DrawSprite(sx, sy, 50.0f, 50.0f,
			tx, ty, 0.2f, 0.2f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	int bullet03Num = GetPlayer().bullet03Num;
	for (int i = 0; i < BULLETUSE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = bullet03Num % 10;			//下一桁だけ抽出

		//テクスチャ座標始点を計算
		tx = (n % 5) * 0.2f;
		ty = (n / 5) * 0.2f;

		bullet03Num /= 10;			//桁を一つ右にずらす

		float sx, sy;
		sx = BULLETUSE_POSX + 150.0f + 30.0f * (BULLETUSE_FIGURE - 1 - i);
		sy = BULLETUSE_03_POSY;

		DrawSprite(sx, sy, 50.0f, 50.0f,
			tx, ty, 0.2f, 0.2f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

BULLET* GetBullet(void)
{
	return g_bullet;
}

void SetBullet(Float2 pos, Float2 vel, Float2 size, bulletType type)
{
	switch (type)
	{
	case BULLET_TYPE1:
		PlaySE(WSD_SE_BULLET01);
		break;
	case BULLET_TYPE2:
		PlaySE(WSD_SE_BULLET02);
		break;
	case BULLET_TYPE3:
		PlaySE(WSD_SE_BULLET03);
		break;
	default:
		break;
	}
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!g_bullet[i].isUse)
		{
			g_bullet[i].pos = pos;
			g_bullet[i].vel = vel;
			g_bullet[i].size = size;;
			g_bullet[i].type = type;
			g_bullet[i].isUse = true;
			switch (g_bullet[i].type)
			{
			case BULLET_TYPE1:
				g_bullet[i].damage = 1;
				g_bullet[i].isShieldIgnore = false;
				break;
			case BULLET_TYPE2:
				g_bullet[i].damage = 1;
				g_bullet[i].isShieldIgnore = true;
				break;
			case BULLET_TYPE3:
				g_bullet[i].damage = 1;
				g_bullet[i].isShieldIgnore = true;
				break;
			default:
				break;
			}

			break;
		}
	}
}