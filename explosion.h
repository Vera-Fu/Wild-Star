//---------------------------------------------------------------
//explosion.h
//
//												�쐬�ҁFFU YIZHI
//												�쐬���F2021/06/14
//---------------------------------------------------------------
#pragma once
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

//�}�N����`
#define MAX_EXPLOSION 100

typedef enum {
	EXPLOSION_TYPE1 = 0,
	EXPLOSION_TYPE2,
	EXPLOSION_TYPE3,
	EXPLOSION_TYPE4,
	EXPLOSION_TYPE_MAX
}EXPLOSIONTYPE;

typedef struct {
	Float2 pos;
	Float2 size;
	EXPLOSIONTYPE type;
	bool isUse;

	int frame;
}EXPLOSION;

//�v���g�^�C�v�錾
void InitExplosion();
void UninitExplosion();
void UpdateExplosion();
void DrawExplosion();

EXPLOSION* GetExplosion(void);
void SetExplosion(Float2 pos, Float2 size, EXPLOSIONTYPE type);

#endif