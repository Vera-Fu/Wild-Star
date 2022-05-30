//---------------------------------------------------------------
//score.h
//
//												�쐬�ҁFFU YIZHI
//												�쐬���F2021/06/18
//---------------------------------------------------------------
#pragma once
#ifndef SCORE_H_
#define SCORE_H_

#define SCORE_FIGURE 6

//�v���g�^�C�v�錾
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