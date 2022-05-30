//---------------------------------------------------------------
//score.cpp
//
//												作成者：FU YIZHI
//												作成日：2021/6/14
//---------------------------------------------------------------
#include "main.h"
#include "texture.h"
#include "sprite.h"

#include "score.h"
#include "levelchoose.h"

int g_score;
int max_score;
Float2 g_ScorePos;
unsigned int g_ScoreTexture;

void InitScore()
{
	g_score = 0;
	g_ScoreTexture = LoadTexture("rom:/number.tga");
	g_ScorePos = MakeFloat2(600.0f, -400.0f);
	for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
	{
		if ((GetLevel() + levelNum)->isChoose)
		{
			max_score = (GetLevel() + levelNum)->maxScore;
		}
	}
}

void UninitScore()
{
	UnloadTexture(g_ScoreTexture);
}

void UpdateScore()
{
	if (g_score > max_score)
	{
		max_score = g_score;
		for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
		{
			if ((GetLevel() + levelNum)->isChoose)
			{
				(GetLevel() + levelNum)->maxScore = max_score;
			}
		}
	}
}

void DrawScore()
{
	SetTexture(g_ScoreTexture);

	int score;
	score = g_score;
	for (int i = 0; i < SCORE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = score % 10;			//下一桁だけ抽出

		//テクスチャ座標始点を計算
		tx = (n % 5)*0.2f;
		ty = (n / 5)*0.2f;

		score /= 10;			//桁を一つ右にずらす

		float sx, sy;
		sx = g_ScorePos.x + 50.0f * (SCORE_FIGURE - 1 - i);
		sy = g_ScorePos.y;

		DrawSprite(sx, sy, 80.0f, 80.0f,
			tx, ty, 0.2f, 0.2f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

void AddScore(int score)
{
	g_score += score;
}

void SetScore(int score)
{
	g_score = score;
}

int GetScore(void)
{
	return g_score;
}

void SetScorePosition(Float2 pos)
{
	g_ScorePos = pos;
}

int GetMaxScore(void)
{
	return max_score;
}
