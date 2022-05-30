#include "main.h"
#include "sprite.h"
#include "texture.h"

#include "UI.h"
#include "levelchoose.h"
#include "shop.h"
#include "levelbg.h"
#include "score.h"
#include "player.h"

bool isShowingUI = false;

//const float LEVEL_01_UI_SIZEX = 600.0f;
//const float LEVEL_01_UI_SIZEY = 700.0f;
//const float XBTN_SIZE = 50.0f;
//const float XBTN_POSX = LEVEL_01_UI_SIZEX / 2 - XBTN_SIZE / 2;
//const float XBTN_POSY = -LEVEL_01_UI_SIZEY / 2 + XBTN_SIZE / 2;

unsigned int g_LevelUITexture[LEVEL_MAX];
unsigned int g_LevelStartBTNTexture;
unsigned int g_xBTNTexture;
unsigned int g_UIGTexture;

unsigned int g_ShopNumTexture;
unsigned int g_ShopUITexture;
unsigned int g_ShopBTNDownTexture;
unsigned int g_ShopBTNUpTexture;
unsigned int g_UpgradeBTNDownTexture;
unsigned int g_UpgradeBTNUpTexture;

unsigned int g_ShopBuyBTNTexture;
unsigned int g_ShopBullet02Texture;
unsigned int g_ShopBullet03Texture;

unsigned int g_UpgradeShootspeedTexture;
unsigned int g_UpgradeHPTexture;
unsigned int g_UpgradeShieldTexture;
unsigned int g_Upgrade0Texture;
unsigned int g_Upgrade1Texture;

unsigned int g_BattleMenuUITexture;
unsigned int g_ContinueBTNDownTexture;
unsigned int g_ContinueBTNUpTexture;
unsigned int g_BattleQuitBTNDownTexture;
unsigned int g_BattleQuitBTNUpTexture;

unsigned int g_UIRankS;
unsigned int g_UIRankA;
unsigned int g_UIRankB;
unsigned int g_UIRankC;

UI g_ui;

void InitUI()
{
	g_LevelUITexture[LEVEL_01] = LoadTexture("rom:/LEVEL_01_UI.tga");
	g_LevelUITexture[LEVEL_02] = LoadTexture("rom:/LEVEL_02_UI.tga");
	g_LevelUITexture[LEVEL_03] = LoadTexture("rom:/LEVEL_03_UI.tga");
	g_LevelUITexture[LEVEL_04] = LoadTexture("rom:/LEVEL_04_UI.tga");
	g_LevelStartBTNTexture = LoadTexture("rom:/START_buttondown.tga");
	g_xBTNTexture = LoadTexture("rom:/X_button.tga");
	g_UIGTexture = LoadTexture("rom:/G.tga");

	g_ShopNumTexture = LoadTexture("rom:/number.tga");
	g_ShopUITexture = LoadTexture("rom:/shop.tga");
	g_ShopBTNDownTexture = LoadTexture("rom:/SHOP_buttondown.tga");
	g_ShopBTNUpTexture = LoadTexture("rom:/SHOP_buttonup.tga");
	g_UpgradeBTNDownTexture = LoadTexture("rom:/UPGRADE_buttondown.tga");
	g_UpgradeBTNUpTexture = LoadTexture("rom:/UPGRADE_buttonup.tga");

	g_ShopBuyBTNTexture = LoadTexture("rom:/BUY_buttondown.tga");
	g_ShopBullet02Texture = LoadTexture("rom:/shopbullet_02.tga");
	g_ShopBullet03Texture = LoadTexture("rom:/shopbullet_03.tga");

	g_UpgradeShootspeedTexture = LoadTexture("rom:/upgradeshootspeed.tga");
	g_UpgradeHPTexture = LoadTexture("rom:/upgradehp.tga");
	g_UpgradeShieldTexture = LoadTexture("rom:/upgradeshield.tga");
	g_Upgrade0Texture = LoadTexture("rom:/UPGRADE0.tga");
	g_Upgrade1Texture = LoadTexture("rom:/UPGRADE1.tga");

	g_BattleMenuUITexture = LoadTexture("rom:/battlemenu.tga");
	g_ContinueBTNDownTexture = LoadTexture("rom:/CONTINUE_buttondown.tga");
	g_ContinueBTNUpTexture = LoadTexture("rom:/CONTINUE_buttonup.tga");
	g_BattleQuitBTNDownTexture = LoadTexture("rom:/QUIT_buttondown.tga");
	g_BattleQuitBTNUpTexture = LoadTexture("rom:/QUIT_buttonup.tga");

	g_UIRankC = LoadTexture("rom:/RANK_C.tga");
	g_UIRankB = LoadTexture("rom:/RANK_B.tga");
	g_UIRankA = LoadTexture("rom:/RANK_A.tga");
	g_UIRankS = LoadTexture("rom:/RANK_S.tga");

	g_ui = NOTHINGUI;
	InitScore();
}

void UninitUI()
{
	for (int i = 0; i < LEVEL_MAX; i++)
	{
		UnloadTexture(g_LevelUITexture[i]);
	}
	UnloadTexture(g_LevelStartBTNTexture);
	UnloadTexture(g_xBTNTexture);
	UnloadTexture(g_UIGTexture);
	//UninitScore();

	UnloadTexture(g_ShopNumTexture);
	UnloadTexture(g_ShopUITexture);
	UnloadTexture(g_ShopBTNDownTexture);
	UnloadTexture(g_ShopBTNUpTexture);
	UnloadTexture(g_UpgradeBTNDownTexture);
	UnloadTexture(g_UpgradeBTNUpTexture);

	UnloadTexture(g_ShopBuyBTNTexture);
	UnloadTexture(g_ShopBullet02Texture);
	UnloadTexture(g_ShopBullet03Texture);

	UnloadTexture(g_UpgradeShootspeedTexture);
	UnloadTexture(g_UpgradeHPTexture);
	UnloadTexture(g_UpgradeShieldTexture);
	UnloadTexture(g_Upgrade0Texture);
	UnloadTexture(g_Upgrade1Texture);

	UnloadTexture(g_BattleMenuUITexture);
	UnloadTexture(g_ContinueBTNDownTexture);
	UnloadTexture(g_ContinueBTNUpTexture);
	UnloadTexture(g_BattleQuitBTNDownTexture);
	UnloadTexture(g_BattleQuitBTNUpTexture);

	UnloadTexture(g_UIRankC);
	UnloadTexture(g_UIRankB);
	UnloadTexture(g_UIRankA);
	UnloadTexture(g_UIRankS);
}

void UpdateUI()
{
	UpdateScore();
}

void DrawUI()
{
	int bullet02Num = GetPlayer().bullet02Num;
	int bullet03Num = GetPlayer().bullet03Num;
	int shootspeedCost = (GetUpgrade() + SHOOTSPEED)->cost;
	int HPCost = (GetUpgrade() + HP)->cost;
	int shieldCost = (GetUpgrade() + SHIELD)->cost;
	switch (g_ui)
	{
	case LEVELCHOOSEUI:
	{
		for (int levelNum = 0; levelNum < LEVEL_MAX; levelNum++)
		{
			if ((GetLevel() + levelNum)->isChoose)
			{
				SetTexture(g_LevelUITexture[levelNum]);
				DrawSprite(0.0f, 0.0f, LEVEL_UI_SIZEX, LEVEL_UI_SIZEY,
					0.0f, 0.0f, 1.0f, 1.0f,
					MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
				switch ((GetLevel() + levelNum)->maxRank)
				{
				case C:
					SetTexture(g_UIRankC);
					break;
				case B:
					SetTexture(g_UIRankB);
					break;
				case A:
					SetTexture(g_UIRankA);
					break; 
				case S:
					SetTexture(g_UIRankS);
					break;
				default:
					break;
				}
				DrawSprite(0.0f, 200.0f, 150.0f, 150.0f,
					0.0f, 0.0f, 1.0f, 1.0f,
					MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
				SetScore((GetLevel() + levelNum)->maxScore);
				
			}
		}
		

		SetTexture(g_xBTNTexture);
		DrawSprite(LEVELXBTN_POSX, LEVELXBTN_POSY, XBTN_SIZE, XBTN_SIZE,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_LevelStartBTNTexture);
		DrawSprite(0.0f, LEVELSTARTBTN_POSY, LEVELSTARTBTN_SIZEX, LEVELSTARTBTN_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetScorePosition(MakeFloat2(-50.0f, -50.0f));
		DrawScore();
		break;
	}
		
	case SHOPMAINUI:
	{
		SetTexture(g_ShopUITexture);
		DrawSprite(0.0f, 0.0f, SHOP_UI_SIZEX, SHOP_UI_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_xBTNTexture);
		DrawSprite(SHOPXBTN_POSX, SHOPXBTN_POSY, XBTN_SIZE, XBTN_SIZE,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		switch (GetSMBTN())
		{
		case BTN_SHOP:
			SetTexture(g_ShopBTNDownTexture);
			DrawSprite(0.0f, SHOP_BTN_POSY, SHOP_BTN_SIZEX, SHOP_BTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

			SetTexture(g_UpgradeBTNUpTexture);
			DrawSprite(0.0f, UPGRADE_BTN_POSY, SHOP_BTN_SIZEX, SHOP_BTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case BTN_UPGRADE:
			SetTexture(g_ShopBTNUpTexture);
			DrawSprite(0.0f, SHOP_BTN_POSY, SHOP_BTN_SIZEX, SHOP_BTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

			SetTexture(g_UpgradeBTNDownTexture);
			DrawSprite(0.0f, UPGRADE_BTN_POSY, SHOP_BTN_SIZEX, SHOP_BTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		default:
			break;
		}
		break;
	}
		
	case SHOPUI:
	{
		SetTexture(g_ShopUITexture);
		DrawSprite(0.0f, 0.0f, SHOP_UI_SIZEX, SHOP_UI_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_xBTNTexture);
		DrawSprite(SHOPXBTN_POSX, SHOPXBTN_POSY, XBTN_SIZE, XBTN_SIZE,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_ShopBullet02Texture);
		DrawSprite(SHOPBULLET_02_POSX, SHOPBULLET_POSY, SHOPBULLET_SIZE, SHOPBULLET_SIZE,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_ShopBullet03Texture);
		DrawSprite(SHOPBULLET_03_POSX, SHOPBULLET_POSY, SHOPBULLET_SIZE, SHOPBULLET_SIZE,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_ShopBuyBTNTexture);
		DrawSprite(SHOPBUYBTN_02_POSX, SHOPBUYBTN_POSY, SHOPBUYBTN_SIZEX, SHOPBUYBTN_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_ShopBuyBTNTexture);
		DrawSprite(SHOPBUYBTN_03_POSX, SHOPBUYBTN_POSY, SHOPBUYBTN_SIZEX, SHOPBUYBTN_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_ShopNumTexture);

		for (int i = 0; i < SHOPBULLET_FIGURE; i++)
		{
			int n;
			float tx, ty;

			n = bullet02Num % 10;			//下一桁だけ抽出

			//テクスチャ座標始点を計算
			tx = (n % 5) * 0.2f;
			ty = (n / 5) * 0.2f;

			bullet02Num /= 10;			//桁を一つ右にずらす

			float sx, sy;
			sx = SHOPBULLET_02_POSX + 30.0f * (SHOPBULLET_FIGURE - 1 - i);
			sy = SHOPBUYBTN_POSY - SHOPBULLET_SIZE - 50.0f;

			DrawSprite(sx, sy, 50.0f, 50.0f,
				tx, ty, 0.2f, 0.2f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		for (int i = 0; i < SHOPBULLET_FIGURE; i++)
		{
			int n;
			float tx, ty;

			n = bullet03Num % 10;			//下一桁だけ抽出

			//テクスチャ座標始点を計算
			tx = (n % 5) * 0.2f;
			ty = (n / 5) * 0.2f;

			bullet03Num /= 10;			//桁を一つ右にずらす

			float sx, sy;
			sx = SHOPBULLET_03_POSX + 30.0f * (SHOPBULLET_FIGURE - 1 - i);
			sy = SHOPBUYBTN_POSY - SHOPBULLET_SIZE - 50.0f;

			DrawSprite(sx, sy, 50.0f, 50.0f,
				tx, ty, 0.2f, 0.2f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		break;
	}	

	case UPGRADEUI:
	{
		SetTexture(g_ShopUITexture);
		DrawSprite(0.0f, 0.0f, SHOP_UI_SIZEX, SHOP_UI_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_xBTNTexture);
		DrawSprite(SHOPXBTN_POSX, SHOPXBTN_POSY, XBTN_SIZE, XBTN_SIZE,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		//Shootspeed
		SetTexture(g_UpgradeShootspeedTexture);
		DrawSprite(UPGRADEBG_POSX, UPGRADEBG_SHOOTSPEED_POSY, UPGRADEBG_SIZEX, UPGRADEBG_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_Upgrade0Texture);
		for (int i = 0; i < UPGRADE_LEVEL_MAX; i++)
		{
			DrawSprite(UPGRADEBG_POSX - 300.0f + 150.0f * i, UPGRADEBG_SHOOTSPEED_POSY + 40.0f, UPGRADE_LEVEL_SIZEX, UPGRADE_LEVEL_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		SetTexture(g_Upgrade1Texture);
		for (int i = 0; i < (GetUpgrade() + SHOOTSPEED)->level; i++)
		{
			DrawSprite(UPGRADEBG_POSX - 300.0f + 150.0f * i, UPGRADEBG_SHOOTSPEED_POSY + 40.0f, UPGRADE_LEVEL_SIZEX, UPGRADE_LEVEL_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		SetTexture(g_UpgradeBTNUpTexture);
		DrawSprite(UPGRADE_BTN_POSX, UPGRADEBG_SHOOTSPEED_POSY, UPGRADE_BTN_SIZEX, UPGRADE_BTN_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		if ((GetUpgrade() + SHOOTSPEED)->level < UPGRADE_LEVEL_MAX) 
		{
			SetTexture(g_ShopNumTexture);
			for (int i = 0; i < COST_FIGURE; i++)
			{
				int n;
				float tx, ty;

				n = shootspeedCost % 10;			//下一桁だけ抽出

				//テクスチャ座標始点を計算
				tx = (n % 5) * 0.2f;
				ty = (n / 5) * 0.2f;

				shootspeedCost /= 10;			//桁を一つ右にずらす

				float sx, sy;
				sx = UPGRADE_BTN_POSX - 60.0f + 30.0f * (COST_FIGURE - 1 - i);
				sy = UPGRADEBG_SHOOTSPEED_POSY + UPGRADE_BTN_SIZEY;

				DrawSprite(sx, sy, 40.0f, 40.0f,
					tx, ty, 0.2f, 0.2f,
					MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			SetTexture(g_UIGTexture);
			DrawSprite(UPGRADE_BTN_POSX + 60.0f, UPGRADEBG_SHOOTSPEED_POSY + UPGRADE_BTN_SIZEY, 30.0f, 30.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}	

		//HP
		SetTexture(g_UpgradeHPTexture);
		DrawSprite(UPGRADEBG_POSX, UPGRADEBG_HP_POSY, UPGRADEBG_SIZEX, UPGRADEBG_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_Upgrade0Texture);
		for (int i = 0; i < UPGRADE_LEVEL_MAX; i++)
		{
			DrawSprite(UPGRADEBG_POSX - 300.0f + 150.0f * i, UPGRADEBG_HP_POSY + 40.0f, UPGRADE_LEVEL_SIZEX, UPGRADE_LEVEL_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		SetTexture(g_Upgrade1Texture);
		for (int i = 0; i < (GetUpgrade() + HP)->level; i++)
		{
			DrawSprite(UPGRADEBG_POSX - 300.0f + 150.0f * i, UPGRADEBG_HP_POSY + 40.0f, UPGRADE_LEVEL_SIZEX, UPGRADE_LEVEL_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		SetTexture(g_UpgradeBTNUpTexture);
		DrawSprite(UPGRADE_BTN_POSX, UPGRADEBG_HP_POSY, UPGRADE_BTN_SIZEX, UPGRADE_BTN_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		if ((GetUpgrade() + HP)->level < UPGRADE_LEVEL_MAX)
		{
			SetTexture(g_ShopNumTexture);
			for (int i = 0; i < COST_FIGURE; i++)
			{
				int n;
				float tx, ty;

				n = HPCost % 10;			//下一桁だけ抽出

				//テクスチャ座標始点を計算
				tx = (n % 5) * 0.2f;
				ty = (n / 5) * 0.2f;

				HPCost /= 10;			//桁を一つ右にずらす

				float sx, sy;
				sx = UPGRADE_BTN_POSX - 60.0f + 30.0f * (COST_FIGURE - 1 - i);
				sy = UPGRADEBG_HP_POSY + UPGRADE_BTN_SIZEY;

				DrawSprite(sx, sy, 40.0f, 40.0f,
					tx, ty, 0.2f, 0.2f,
					MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			SetTexture(g_UIGTexture);
			DrawSprite(UPGRADE_BTN_POSX + 60.0f, UPGRADEBG_HP_POSY + UPGRADE_BTN_SIZEY, 30.0f, 30.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//SHIELD
		SetTexture(g_UpgradeShieldTexture);
		DrawSprite(UPGRADEBG_POSX, UPGRADEBG_SHIELD_POSY, UPGRADEBG_SIZEX, UPGRADEBG_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		SetTexture(g_Upgrade0Texture);
		for (int i = 0; i < UPGRADE_LEVEL_MAX; i++)
		{
			DrawSprite(UPGRADEBG_POSX - 300.0f + 150.0f * i, UPGRADEBG_SHIELD_POSY + 40.0f, UPGRADE_LEVEL_SIZEX, UPGRADE_LEVEL_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		SetTexture(g_Upgrade1Texture);
		for (int i = 0; i < (GetUpgrade() + SHIELD)->level; i++)
		{
			DrawSprite(UPGRADEBG_POSX - 300.0f + 150.0f * i, UPGRADEBG_SHIELD_POSY + 40.0f, UPGRADE_LEVEL_SIZEX, UPGRADE_LEVEL_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		SetTexture(g_UpgradeBTNUpTexture);
		DrawSprite(UPGRADE_BTN_POSX, UPGRADEBG_SHIELD_POSY, UPGRADE_BTN_SIZEX, UPGRADE_BTN_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

		if ((GetUpgrade()+SHIELD)->level < UPGRADE_LEVEL_MAX)
		{
			SetTexture(g_ShopNumTexture);
			for (int i = 0; i < COST_FIGURE; i++)
			{
				int n;
				float tx, ty;

				n = shieldCost % 10;			//下一桁だけ抽出

				//テクスチャ座標始点を計算
				tx = (n % 5) * 0.2f;
				ty = (n / 5) * 0.2f;

				shieldCost /= 10;			//桁を一つ右にずらす

				float sx, sy;
				sx = UPGRADE_BTN_POSX - 60.0f + 30.0f * (COST_FIGURE - 1 - i);
				sy = UPGRADEBG_SHIELD_POSY + UPGRADE_BTN_SIZEY;

				DrawSprite(sx, sy, 40.0f, 40.0f,
					tx, ty, 0.2f, 0.2f,
					MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			SetTexture(g_UIGTexture);
			DrawSprite(UPGRADE_BTN_POSX + 60.0f, UPGRADEBG_SHIELD_POSY + UPGRADE_BTN_SIZEY, 30.0f, 30.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		
		break;
	}
	case BATTLEMENUUI:
	{
		SetTexture(g_BattleMenuUITexture);
		DrawSprite(0.0f, 0.0f, BATTLEMENU_UI_SIZEX, BATTLEMENU_UI_SIZEY,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		switch (GetBMBTN())
		{
		case BTN_CONTINUE:
			SetTexture(g_ContinueBTNDownTexture);
			DrawSprite(0.0f, BATTLEMENUCONTINUEBTN_POSY, BATTLEMENUBTN_SIZEX, BATTLEMENUBTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

			SetTexture(g_BattleQuitBTNUpTexture);
			DrawSprite(0.0f, BATTLEMENUQUITBTN_POSY, BATTLEMENUBTN_SIZEX, BATTLEMENUBTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case BTN_BATTLEQUIT:
			SetTexture(g_ContinueBTNUpTexture);
			DrawSprite(0.0f, BATTLEMENUCONTINUEBTN_POSY, BATTLEMENUBTN_SIZEX, BATTLEMENUBTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

			SetTexture(g_BattleQuitBTNDownTexture);
			DrawSprite(0.0f, BATTLEMENUQUITBTN_POSY, BATTLEMENUBTN_SIZEX, BATTLEMENUBTN_SIZEY,
				0.0f, 0.0f, 1.0f, 1.0f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));;
			break;
		default:
			break;
		}
		break;
	}
	case RESULTUI:
		break;
	case NOTHINGUI:
		break;
	default:
		break;
	}
	
}

void ShowUI(UI ui)
{
	g_ui = ui;
}
