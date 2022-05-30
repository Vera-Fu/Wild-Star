//---------------------------------------------------------------
//title.h
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/25
//---------------------------------------------------------------
#pragma once

#ifndef TITLE_H_
#define TITLE_H_

typedef enum
{
	BTN_START = 0,
	BTN_QUIT
}TITLEBTN;

void InitTitle();
void UninitTitle();
void UpdateTitle();
void DrawTitle();

TITLEBTN GetBTN(void);

#endif // !TITLE_H_


