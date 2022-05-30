#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "controller.h"

#include "shop.h"
#include "levelchoose.h"
#include "player.h"
#include "UI.h"
#include "sound.h"

unsigned int g_ShopChooseTexture;
unsigned int g_ShopMoneyTexture;
unsigned int g_GTexture;

LEVEL g_shop;
SHOPMENUBTN g_shopmenubtn;
UPGRADE g_upgrade[STATUS_MAX];


bool isTouch;
bool isUsing;

void InitShop()
{
	g_ShopChooseTexture = LoadTexture("rom:/shopstar.tga");
	g_ShopMoneyTexture = LoadTexture("rom:/number.tga");
	g_GTexture = LoadTexture("rom:/G.tga");

	g_shop.pos = MakeFloat2(-900.0f, -500.0f);
	g_shop.size = MakeFloat2(LEVELCHOOSESIZE, LEVELCHOOSESIZE);
	g_shop.isUse = true;
	g_shop.isChoose = false;
	g_shop.isUnlock = true;
	g_shop.levelnum = SHOP;

	if (g_upgrade[SHOOTSPEED].level == 0)
	{
		g_upgrade[SHOOTSPEED].cost = 200;
	}
	if (g_upgrade[HP].level == 0)
	{
		g_upgrade[HP].cost = 100;
	}
	if (g_upgrade[SHIELD].level == 0)
	{
		g_upgrade[SHIELD].cost = 100;
	}
	
	g_shopmenubtn = BTN_SHOP;
	isTouch = false;
	
}

void UninitShop()
{
	UnloadTexture(g_ShopChooseTexture);
	UnloadTexture(g_ShopMoneyTexture);
}

void UpdateShop()
{
	if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();

		if (GetIsTouch(touch, LEVELCHOOSESIZE / 2, LEVELCHOOSESIZE / 2, g_shop.pos.x, g_shop.pos.y) &&
			!GetIslevelTouch() &&
			!g_shop.isChoose)
		{
			PlaySE(WSD_SE_CLICK);
			SetIslevelTouch(true);
			g_shop.isChoose = true;
			ShowUI(SHOPMAINUI);
		}
		if (GetIsTouch(touch, XBTN_SIZE / 2, XBTN_SIZE / 2, SHOPXBTN_POSX, SHOPXBTN_POSY) &&
			GetIslevelTouch() &&
			g_shop.isChoose)
		{
			PlaySE(WSD_SE_UIMOVE);
			SetIslevelTouch(false);
			g_shop.isChoose = false;
			isUsing = false;
			ShowUI(NOTHINGUI);
		}	
	}

	if (g_shop.isChoose)
	{
		if (GetControllerTouchScreen())
		{
			Float2 touch;
			touch = GetControllerTouchScreenPosition();
			if (GetIsTouch(touch, SHOP_BTN_SIZEX / 2, SHOP_BTN_SIZEY / 2, 0.0f, SHOP_BTN_POSY) && !isUsing)
			{
				PlaySE(WSD_SE_CLICK);
				g_shopmenubtn = BTN_SHOP;
				isUsing = true;
				ShowUI(SHOPUI);
			}
			if (GetIsTouch(touch, SHOP_BTN_SIZEX / 2, SHOP_BTN_SIZEY / 2, 0.0f, UPGRADE_BTN_POSY) && !isUsing)
			{
				PlaySE(WSD_SE_CLICK);
				g_shopmenubtn = BTN_UPGRADE;
				isUsing = true;
				ShowUI(UPGRADEUI);
			}
		}

		if ((GetControllerTrigger(NpadButton::Down::Index) ||
			GetControllerTrigger(NpadButton::Up::Index) ||
			GetControllerTrigger(NpadButton::StickLDown::Index) ||
			GetControllerTrigger(NpadButton::StickLUp::Index)) && 
			!isUsing)
		{
			PlaySE(WSD_SE_UIMOVE);
			switch (g_shopmenubtn)
			{
			case BTN_SHOP:
				g_shopmenubtn = BTN_UPGRADE;
				break;
			case BTN_UPGRADE:
				g_shopmenubtn = BTN_SHOP;
				break;
			default:
				break;
			}
		}
		if (GetControllerTrigger(NpadButton::B::Index) && !isUsing)
		{
			PlaySE(WSD_SE_UIMOVE);
			SetIslevelTouch(false);
			g_shop.isChoose = false;
			ShowUI(NOTHINGUI);
		}
		if (GetControllerTrigger(NpadButton::A::Index) && !isUsing)
		{
			PlaySE(WSD_SE_CLICK);
			switch (g_shopmenubtn)
			{
			case BTN_SHOP:
				g_shopmenubtn = BTN_SHOP;
				isUsing = true;
				ShowUI(SHOPUI);
				break;
			case BTN_UPGRADE:
				g_shopmenubtn = BTN_UPGRADE;
				isUsing = true;
				ShowUI(UPGRADEUI);
				break;
			default:
				break;
			}
		}
	}

	if (isUsing)
	{
		if (GetControllerTrigger(NpadButton::B::Index))
		{
			PlaySE(WSD_SE_UIMOVE);
			isUsing = false;
			ShowUI(SHOPMAINUI);
		}
	}

	if (isUsing && g_shopmenubtn == BTN_SHOP)
	{
		if (GetControllerTouchScreen() && !isTouch)
		{
			isTouch = true;
			Float2 touch;
			touch = GetControllerTouchScreenPosition();
			if (GetIsTouch(touch, SHOPBUYBTN_SIZEX / 2, SHOPBUYBTN_SIZEY / 2, SHOPBUYBTN_02_POSX, SHOPBUYBTN_POSY) && GetPlayer().money >= 10)
			{
				PlaySE(WSD_SE_CLICK);
				AddPlayerBullet02();
				ChangePlayerMoney(-10);
			}
			if (GetIsTouch(touch, SHOPBUYBTN_SIZEX / 2, SHOPBUYBTN_SIZEY / 2, SHOPBUYBTN_03_POSX, SHOPBUYBTN_POSY) && GetPlayer().money >= 20)
			{
				PlaySE(WSD_SE_CLICK);
				AddPlayerBullet03();
				ChangePlayerMoney(-20);
			}
		}
		if (!GetControllerTouchScreen())
		{
			isTouch = false;
		}
	}

	if (isUsing && g_shopmenubtn == BTN_UPGRADE)
	{
		if (GetControllerTouchScreen() && !isTouch)
		{
			isTouch = true;
			Float2 touch;
			touch = GetControllerTouchScreenPosition();
			if (GetIsTouch(touch, UPGRADE_BTN_SIZEX / 2, UPGRADE_BTN_SIZEY / 2, UPGRADE_BTN_POSX, UPGRADEBG_SHOOTSPEED_POSY) && 
				GetPlayer().money >= g_upgrade[SHOOTSPEED].cost &&
				g_upgrade[SHOOTSPEED].level < UPGRADE_LEVEL_MAX)
			{
				PlaySE(WSD_SE_CLICK);
				ChangePlayerMoney(-g_upgrade[SHOOTSPEED].cost);
				g_upgrade[SHOOTSPEED].cost *= 2;
				g_upgrade[SHOOTSPEED].level += 1;
				SetPlayerShootSpeed(GetPlayer().shootSpeed - 2);
			}
			if (GetIsTouch(touch, UPGRADE_BTN_SIZEX / 2, UPGRADE_BTN_SIZEY / 2, UPGRADE_BTN_POSX, UPGRADEBG_HP_POSY) &&
				GetPlayer().money >= g_upgrade[HP].cost &&
				g_upgrade[HP].level < UPGRADE_LEVEL_MAX)
			{
				PlaySE(WSD_SE_CLICK);
				ChangePlayerMoney(-g_upgrade[HP].cost);
				g_upgrade[HP].cost *= 2;
				g_upgrade[HP].level += 1;
				SetPlayerMaxHP(GetPlayer().maxHP + 1);
			}
			if (GetIsTouch(touch, UPGRADE_BTN_SIZEX / 2, UPGRADE_BTN_SIZEY / 2, UPGRADE_BTN_POSX, UPGRADEBG_SHIELD_POSY) &&
				GetPlayer().money >= g_upgrade[SHIELD].cost &&
				g_upgrade[SHIELD].level < UPGRADE_LEVEL_MAX)
			{
				PlaySE(WSD_SE_CLICK);
				ChangePlayerMoney(-g_upgrade[SHIELD].cost);
				g_upgrade[SHIELD].cost *= 2;
				g_upgrade[SHIELD].level += 1;
				SetPlayerMaxShield(GetPlayer().maxShield + 2);
			}
		}
		if (!GetControllerTouchScreen())
		{
			isTouch = false;
		}
	}
}

void DrawShop()
{
	SetTexture(g_ShopChooseTexture);

	DrawSprite(g_shop.pos.x, g_shop.pos.y, g_shop.size.x, g_shop.size.y,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	if (g_shop.isChoose)
	{
		int money = GetPlayer().money;
		SetTexture(g_ShopMoneyTexture);

		for (int i = 0; i < MONEY_FIGURE; i++)
		{
			int n;
			float tx, ty;

			n = money % 10;			//下一桁だけ抽出

			//テクスチャ座標始点を計算
			tx = (n % 5) * 0.2f;
			ty = (n / 5) * 0.2f;

			money /= 10;			//桁を一つ右にずらす

			float sx, sy;
			sx = SCREEN_WIDTH / 2 - 200.0f + 30.0f * (MONEY_FIGURE - 1 - i);
			sy = SCREEN_HEIGHT / 2 - 50.0f;

			DrawSprite(sx, sy, 50.0f, 50.0f,
				tx, ty, 0.2f, 0.2f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		SetTexture(g_GTexture);
		DrawSprite(SCREEN_WIDTH / 2 - 45.0f, SCREEN_HEIGHT / 2 - 50.0f, 40.0f, 40.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
}

SHOPMENUBTN GetSMBTN(void)
{
	return g_shopmenubtn;
}

UPGRADE* GetUpgrade(void)
{
	return g_upgrade;
}
