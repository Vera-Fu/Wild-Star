#pragma once
#ifndef SHOP_H_
#define SHOP_H_

#define SHOP_BTN_SIZEX 400
#define SHOP_BTN_SIZEY 75

#define SHOP_BTN_POSY -200
#define UPGRADE_BTN_POSY 200

#define SHOPBULLET_FIGURE 3
#define MONEY_FIGURE 5
#define COST_FIGURE 4

#define UPGRADE_LEVEL_MAX 5

typedef enum 
{
	BTN_SHOP = 0,
	BTN_UPGRADE
}SHOPMENUBTN;

typedef enum {
	SHOOTSPEED = 0,
	HP,
	SHIELD,
	STATUS_MAX
}STATUS;

typedef struct {
	int level = 0;
	int cost;
}UPGRADE;

void InitShop();
void UninitShop();
void UpdateShop();
void DrawShop();

SHOPMENUBTN GetSMBTN(void);
UPGRADE* GetUpgrade(void);

#endif // !SHOP_H_

