//---------------------------------------------------------------
//enemy.h
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/07
//---------------------------------------------------------------
#pragma once
#ifndef ENEMY_H_
#define ENEMY_H_

#define MAX_ENEMY 1000
#define FPS 60
#define LEVEL01_ENEMY01_SIZEX 90.0f
#define LEVEL01_ENEMY01_SIZEY 90.0f
#define LEVEL01_ENEMY02_SIZEX 140.0f
#define LEVEL01_ENEMY02_SIZEY 140.0f
#define LEVEL01_ENEMY03_SIZEX 200.0f
#define LEVEL01_ENEMY03_SIZEY 400.0f
#define LEVEL01_BOSS01_SIZEX 400.0f
#define LEVEL01_BOSS01_SIZEY 400.0f
#define LEVEL01_BOSS02_SIZEX 500.0f
#define LEVEL01_BOSS02_SIZEY 500.0f
#define LEVEL02_BOSS_SIZEX 800.0f
#define LEVEL02_BOSS_SIZEY 600.0f

typedef enum{
	ENEMY_TYPE0,
	LEVEL01_ENEMY_01,
	LEVEL01_ENEMY_02,
	LEVEL01_ENEMY_03,
	LEVEL01_BOSS_01,
	LEVEL01_BOSS_02,
	LEVEL02_BOSS,
	ENEMY_TYPE_MAX
}enemyType;

typedef struct {
	Float2 pos;
	Float2 vel;
	Float2 size;
	int HP;
	int shield;
	enemyType type;
	int shootTimer;
	int shootRot;
	int score;
	bool isUse;
	bool isChangeMode;
}ENEMY;

void InitEnemy();
void UninitEnemy();
void UpdateEnemy();
void DrawEnemy();

ENEMY* GetEnemy(void);
void SetEnemy(Float2 pos, enemyType type);

#endif // !1


