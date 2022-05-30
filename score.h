//---------------------------------------------------------------
//score.h
//
//												作成者：FU YIZHI
//												作成日：2021/06/18
//---------------------------------------------------------------
#pragma once
#ifndef SCORE_H_
#define SCORE_H_

#define SCORE_FIGURE 6

//プロトタイプ宣言
void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int score);
void SetScore(int score);
int GetScore(void);
void SetScorePosition(Float2 pos);
int GetMaxScore(void);

#endif