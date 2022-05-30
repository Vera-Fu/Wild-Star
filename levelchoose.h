#pragma once
#ifndef LEVELCHOOSE_H_
#define LEVELCHOOSE_H_

#define LEVELCHOOSESIZE 200.0f

typedef enum
{
	LEVEL_01 = 0,
	LEVEL_02,
	LEVEL_03,
	LEVEL_04,
	LEVEL_MAX,
	SHOP
}LEVELNUM;

typedef enum
{
	C = 0,
	B,
	A,
	S,
}RANK;

typedef struct {
	Float2 pos;
	Float2 size;
	int maxScore = 0;
	RANK rank = C;
	RANK maxRank = C;
	bool isBossDefeted;
	bool isUse;
	bool isUnlock = false;
	bool isChoose = false;
	LEVELNUM levelnum = LEVEL_01;
}LEVEL;

void InitLevelChoose();
void UninitLevelChoose();
void UpdateLevelChoose();
void DrawLevelChoose();

LEVEL* GetLevel(void);
void SetLevel(Float2 pos, LEVELNUM levelnum);

bool GetIslevelTouch(void);
void SetIslevelTouch(bool ilt);
void SetIsBossDefeted(LEVELNUM levelnum);
void SetIsLevelUnlock(LEVELNUM levelnum);

#endif // !LEVELCHOOSE_H_


