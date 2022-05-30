//---------------------------------------------------------------
//result.cpp
//
//												�쐬�ҁFFU YIZHI
//												�쐬���F2021/6/25
//---------------------------------------------------------------

#include "main.h"
#include "result.h"
#include "resultbg.h"
#include "controller.h"
#include "fade.h"

void InitResult()
{
	InitResultBG();
}


void UninitResult()
{
	UninitResultBG();
	//UninitScore();
}

void UpdateResult()
{
	UpdateResultBG();
	if (GetControllerTrigger(NpadButton::L::Index))
	{
		//SetScene(SCENE_TITLE);
		SetFade(FADEMODE_OUT);
	}
}


void DrawResult()
{
	DrawResultBG();
}