//---------------------------------------------------------------
//fade.h
//
//												作成者：FU YIZHI
//												作成日：2021/07/05
//---------------------------------------------------------------
#pragma once
#ifndef FADE_H_
#define FADE_H_

#define SPEED 60

typedef enum 
{
	FADEMODE_NONE = 0,
	FADEMODE_OUT,
	FADEMODE_IN,
	FADEMODE_MAX
}FADEMODE;

//プロトタイプ宣言
void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

bool SetFade(FADEMODE m);

#endif