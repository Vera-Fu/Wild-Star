//---------------------------------------------------------------
//enemybullet.h
//
//												作成者：FU YIZHI
//												作成日：2021/6/31
//---------------------------------------------------------------
#pragma once
#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

//マクロ定義
#define MAX_ENEMYBULLET 1000
#define ENEMYSHOOTSPEED 5

typedef enum{
	ENEMYBULLET_TYPE0,
	ENEMYBULLET_TYPE1,
	ENEMYBULLET_TYPE2,
	ENEMYBULLET_TYPE3,
	ENEMYBULLET_TYPE4,
	BOSSBULLET_TYPE1,
	BOSSBULLET_TYPE2,
	BOSSBULLET_TYPE3,
	BOSSBULLET_TYPE4,
	ENEMYBULLET_TYPE_MAX
}enemybulletType;

typedef struct {
	Float2 pos;
	Float2 vel;		//速度
	Float2 size;
	enemybulletType type;
	int damage;
	bool isShieldIgnore;
	bool isUse;
}ENEMYBULLET;

//プロトタイプ宣言
void InitEnemyBullet();
void UninitEnemyBullet();
void UpdateEnemyBullet();
void DrawEnemyBullet();

ENEMYBULLET* GetEnemyBullet(void);
void SetEnemyBullet(Float2 pos, Float2 vel, Float2 size, enemybulletType type);

#endif