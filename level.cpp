#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "controller.h"
#include "score.h"

#include "level.h"
#include "levelbg.h"
#include "sound.h"

#include "levelchoose.h"
#include "enemy.h"

int g_SetEnemyTimer;

void InitLevel()
{
	InitLevelBG();

	g_SetEnemyTimer = 0;

	for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
	{
		if ((GetLevel() + levelNum)->isChoose)
		{
			switch (levelNum)
			{
			case LEVEL_01:
				PlayBGM(STRM_BGM_LEVEL01_01);
				break;
			case LEVEL_02:
				PlayBGM(STRM_BGM_LEVEL02);
				break;
			case LEVEL_03:
				PlayBGM(STRM_BGM_LEVEL03);
				break;
			case LEVEL_04:
				PlayBGM(STRM_BGM_LEVEL04);
				break;
			default:
				break;
			}
		}
	}
}


void UninitLevel()
{
	UninitLevelBG();
}


void UpdateLevel()
{
	UpdateLevelBG();
	AddScore(1);
	g_SetEnemyTimer += 1;
	for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
	{
		if ((GetLevel() + levelNum)->isChoose)
		{
			switch (levelNum)
			{
			case LEVEL_01:
			{
				if (SetEnemyTimer(3 * FPS))
				{
					SetEnemy(MakeFloat2(-200.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);	
				}
				if (SetEnemyTimer(6 * FPS))
				{
				}
				if (SetEnemyTimer(9 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(15 * FPS))
				{
					SetEnemy(MakeFloat2(+SCREEN_WIDTH / 4 - LEVEL01_ENEMY02_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY02_SIZEY / 2)), LEVEL01_ENEMY_02);
				}
				if (SetEnemyTimer(20 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(22 * FPS))
				{
					SetEnemy(MakeFloat2(-300.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(24 * FPS))
				{
					SetEnemy(MakeFloat2(+300.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(30 * FPS))
				{
					SetEnemy(MakeFloat2(+SCREEN_WIDTH / 4 - LEVEL01_ENEMY03_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY03_SIZEY / 2)), LEVEL01_ENEMY_03);
				}
				if (SetEnemyTimer(40 * FPS))
				{
					SetEnemy(MakeFloat2(-SCREEN_WIDTH / 4 + LEVEL01_ENEMY03_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY03_SIZEY / 2)), LEVEL01_ENEMY_03);
					SetEnemy(MakeFloat2(+300.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(55 * FPS))
				{
					SetEnemy(MakeFloat2(+SCREEN_WIDTH / 4 - LEVEL01_ENEMY02_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY02_SIZEY / 2)), LEVEL01_ENEMY_02);
					SetEnemy(MakeFloat2(-200.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(60 * FPS))
				{
					SetEnemy(MakeFloat2(+200.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(65 * FPS))
				{
					SetEnemy(MakeFloat2(-SCREEN_WIDTH / 4 + LEVEL01_ENEMY03_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY03_SIZEY / 2)), LEVEL01_ENEMY_03);	
				}
				if (SetEnemyTimer(75 * FPS))
				{
					SetEnemy(MakeFloat2(+300.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(80 * FPS))
				{
					SetEnemy(MakeFloat2(+SCREEN_WIDTH / 4 - LEVEL01_ENEMY02_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY02_SIZEY / 2)), LEVEL01_ENEMY_02);
				}
				if (SetEnemyTimer(82 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}

				if (SetEnemyTimer(90 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_BOSS01_SIZEY / 2)), LEVEL01_BOSS_01);
				}
				if (SetEnemyTimer(120 * FPS))
				{
					SetEnemy(MakeFloat2(-SCREEN_WIDTH / 4 + LEVEL01_ENEMY02_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY02_SIZEY / 2)), LEVEL01_ENEMY_02);
					SetEnemy(MakeFloat2(-100.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(130 * FPS))
				{
					SetEnemy(MakeFloat2(+SCREEN_WIDTH / 4 - LEVEL01_ENEMY02_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY02_SIZEY / 2)), LEVEL01_ENEMY_02);
				}
				if (SetEnemyTimer(135 * FPS))
				{
					SetEnemy(MakeFloat2(-SCREEN_WIDTH / 4 + LEVEL01_ENEMY02_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY02_SIZEY / 2)), LEVEL01_ENEMY_02);
				}
				if (SetEnemyTimer(145 * FPS))
				{
					SetEnemy(MakeFloat2(-120.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
					SetEnemy(MakeFloat2(+120.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
					SetEnemy(MakeFloat2(+360.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
					SetEnemy(MakeFloat2(-360.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
					SetVolumeBGM(0, 600);
					
				}
				if (SetEnemyTimer(160 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_BOSS02_SIZEY / 2)), LEVEL01_BOSS_02);
					StopBGM();
					PlayBGM(STRM_BGM_LEVEL01_02);
					SetVolumeBGM(1, 120);		
				}
				break;
			}
				
			case LEVEL_02:
			{
				if (SetEnemyTimer(5 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, -1000.0f), LEVEL02_BOSS);
				}
				break;
			}
			case LEVEL_03:
			{
				if (SetEnemyTimer(2 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(4 * FPS))
				{
					SetEnemy(MakeFloat2(-300.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(6 * FPS))
				{
					SetEnemy(MakeFloat2(+300.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(10 * FPS))
				{
					SetEnemy(MakeFloat2(+SCREEN_WIDTH / 4 - LEVEL01_ENEMY03_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY03_SIZEY / 2)), LEVEL01_ENEMY_03);
				}
				if (SetEnemyTimer(20 * FPS))
				{
					SetEnemy(MakeFloat2(-SCREEN_WIDTH / 4 + LEVEL01_ENEMY03_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY03_SIZEY / 2)), LEVEL01_ENEMY_03);
					SetEnemy(MakeFloat2(+300.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(35 * FPS))
				{
					SetEnemy(MakeFloat2(+SCREEN_WIDTH / 4 - LEVEL01_ENEMY02_SIZEX / 2, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY02_SIZEY / 2)), LEVEL01_ENEMY_02);
					SetEnemy(MakeFloat2(-200.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(40 * FPS))
				{
					SetEnemy(MakeFloat2(+200.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_ENEMY01_SIZEY / 2)), LEVEL01_ENEMY_01);
				}
				if (SetEnemyTimer(45 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, -1000.0f), LEVEL02_BOSS);
				}			
				break;
			}
			case LEVEL_04:
			{
				if (SetEnemyTimer(5 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_BOSS01_SIZEY / 2)), LEVEL01_BOSS_01);
				}
				if (SetEnemyTimer(35 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, (-SCREEN_HEIGHT / 2 - LEVEL01_BOSS01_SIZEY / 2)), LEVEL01_BOSS_02);
				}
				if (SetEnemyTimer(128 * FPS))
				{
					SetEnemy(MakeFloat2(0.0f, -1000.0f), LEVEL02_BOSS);
				}
				break;
			}
			default:
				break;
			}
		}
	}

}


void DrawLevel()
{
	DrawLevelBG();
}

bool SetEnemyTimer(int time)
{
	if (g_SetEnemyTimer == time)
	{
		return true;
	}
	return false;
}


