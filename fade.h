//---------------------------------------------------------------
//fade.h
//
//												�쐬�ҁFFU YIZHI
//												�쐬���F2021/07/05
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

//�v���g�^�C�v�錾
void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

bool SetFade(FADEMODE m);

#endif