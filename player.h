#pragma once

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

#define MOVEPOS 8.0f

typedef struct {
	Float2 pos;
	Float2 size;
	int HP;
	int maxHP = 5;
	int shield;
	int maxShield = 10;
	int money = 0;
	int shootSpeed = 30;
	int bullet02Num = 0;
	int bullet03Num = 0;
	bool isAlive;
}PLAYER;

PLAYER GetPlayer();
void PlayerLifeDecrease(int val);
void PlayerShieldDecrease(int val);
void SetPlayerMaxHP(int val);
void SetPlayerMaxShield(int val);
void SetPlayerShootSpeed(int val);
void AddPlayerBullet02(void);
void AddPlayerBullet03(void);
void ChangePlayerMoney(int money);
