//---------------------------------------------------------------
//resultbg.cpp
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/25
//---------------------------------------------------------------

#include "main.h"
#include "texture.h"
#include "sprite.h"

#include "resultbg.h"
#include "levelchoose.h"
#include "UI.h"
#include "score.h"
#include "player.h"


unsigned int g_ResultBGTexture[LEVEL_MAX];
unsigned int g_ChangeSceneRETexture;
unsigned int g_RankC;
unsigned int g_RankB;
unsigned int g_RankA;
unsigned int g_RankS;


void InitResultBG()
{
	ShowUI(NOTHINGUI);
	g_ResultBGTexture[LEVEL_01] = LoadTexture("rom:/LEVEL_01_RESULT.tga");
	g_ResultBGTexture[LEVEL_02] = LoadTexture("rom:/LEVEL_02_RESULT.tga");
	g_ResultBGTexture[LEVEL_03] = LoadTexture("rom:/LEVEL_03_RESULT.tga");
	g_ResultBGTexture[LEVEL_04] = LoadTexture("rom:/LEVEL_04_RESULT.tga");
	g_ChangeSceneRETexture = LoadTexture("rom:/changescene.tga");
	g_RankC = LoadTexture("rom:/RANK_C.tga");
	g_RankB = LoadTexture("rom:/RANK_B.tga");
	g_RankA = LoadTexture("rom:/RANK_A.tga");
	g_RankS = LoadTexture("rom:/RANK_S.tga");
	SetScorePosition(MakeFloat2(-50.0f, -45.0f));


	for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
	{
		if ((GetLevel() + levelNum)->isChoose)
		{
			switch ((GetLevel() + levelNum)->levelnum)
			{
			case LEVEL_01:
				if ((GetLevel() + levelNum)->isBossDefeted)
				{
					(GetLevel() + levelNum)->rank = S;
					ChangePlayerMoney(+200);
				}
				else
				{
					if (GetScore() > 9500 && GetScore() < 13000)
					{
						(GetLevel() + levelNum)->rank = B;
						ChangePlayerMoney(+50);
					}
					if (GetScore() >= 13000)
					{
						(GetLevel() + levelNum)->rank = A;
						ChangePlayerMoney(+100);
					}
				}
				break;
			case LEVEL_02:
				if ((GetLevel() + levelNum)->isBossDefeted)
				{
					if (GetScore() >= 18000)
					{
						(GetLevel() + levelNum)->rank = S;
						ChangePlayerMoney(+200);
					}
					else
					{
						(GetLevel() + levelNum)->rank = A;
						ChangePlayerMoney(+100);
					}
				}
				else
				{
					if (GetScore() > 4500 && GetScore() < 7500)
					{
						(GetLevel() + levelNum)->rank = B;
						ChangePlayerMoney(+50);
					}
					if (GetScore() >= 7500)
					{
						(GetLevel() + levelNum)->rank = A;
						ChangePlayerMoney(+100);
					}
				}
				break;
			case LEVEL_03:
				if ((GetLevel() + levelNum)->isBossDefeted)
				{
					(GetLevel() + levelNum)->rank = S;
					ChangePlayerMoney(+200);
				}
				else
				{
					if (GetScore() > 5000 && GetScore() < 8000)
					{
						(GetLevel() + levelNum)->rank = B;
						ChangePlayerMoney(+50);
					}
					if (GetScore() >= 8000)
					{
						(GetLevel() + levelNum)->rank = A;
						ChangePlayerMoney(+100);
					}
				}
				break;
			case LEVEL_04:
				if ((GetLevel() + levelNum)->isBossDefeted)
				{
					(GetLevel() + levelNum)->rank = S;
					ChangePlayerMoney(+200);
				}
				else
				{
					if (GetScore() > 3300 && GetScore() < 13000)
					{
						(GetLevel() + levelNum)->rank = B;
						ChangePlayerMoney(+50);
					}
					if (GetScore() >= 13000)
					{
						(GetLevel() + levelNum)->rank = A;
						ChangePlayerMoney(+100);
					}
				}
				break;
			default:
				break;
			}
			if ((GetLevel() + levelNum)->rank > (GetLevel() + levelNum)->maxRank)
			{
				(GetLevel() + levelNum)->maxRank = (GetLevel() + levelNum)->rank;
			}
		}
	}
}


void UninitResultBG()
{
	for (int i = 0; i < LEVEL_MAX; i++)
	{
		UnloadTexture(g_ResultBGTexture[i]);
	}
	UnloadTexture(g_ChangeSceneRETexture);
	UnloadTexture(g_RankC);
	UnloadTexture(g_RankB);
	UnloadTexture(g_RankA);
	UnloadTexture(g_RankS);
}


void UpdateResultBG()
{
	
}


void DrawResultBG()
{
	for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
	{
		if ((GetLevel() + levelNum)->isChoose)
		{
			SetTexture(g_ResultBGTexture[levelNum]);
			DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			switch ((GetLevel() + levelNum)->rank)
			{
			case C:
				SetTexture(g_RankC);
				break;
			case B:
				SetTexture(g_RankB);
				break;
			case A:
				SetTexture(g_RankA);
				break;
			case S:
				SetTexture(g_RankS);
				break;
			default:
				break;
			}
			DrawSprite(0.0f, 150.0f, 150.0f, 150.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	
	SetTexture(g_ChangeSceneRETexture);

	DrawSprite(0.0f, 300.0f, 500.0f, 400.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	DrawScore();

}