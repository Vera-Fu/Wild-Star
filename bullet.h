//---------------------------------------------------------------
//bullet.h
//
//												作成者：FU YIZHI
//												作成日：2021/5/31
//---------------------------------------------------------------
#pragma once
#ifndef BULLET_H_
#define BULLET_H_

//マクロ定義
#define MAX_BULLET 100

#define BULLETUSE_SIZE 150.0f
#define BULLETUSE_POSX 600.0f
#define BULLETUSE_02_POSY 100.0f
#define BULLETUSE_03_POSY 300.0f
#define BULLETUSE_FIGURE 3

typedef enum {
	BULLET_USE_02 = 0,
	BULLET_USE_03,
	BULLET_USE_MAX
};

typedef enum{
	BULLET_TYPE0,
	BULLET_TYPE1,
	BULLET_TYPE2,
	BULLET_TYPE3,
	BULLET_TYPE_MAX
}bulletType;

typedef struct {
	Float2 pos;
	Float2 vel;		//速度
	Float2 size;
	bulletType type;
	int damage;
	bool isShieldIgnore;
	bool isUse;
}BULLET;
				
//プロトタイプ宣言
void InitBullet();
void UninitBullet();
void UpdateBullet();
void DrawBullet();

BULLET* GetBullet(void);
void SetBullet(Float2 pos, Float2 vel, Float2 size, bulletType type);

#endif