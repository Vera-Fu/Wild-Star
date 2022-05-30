
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "fade.h"


unsigned int	g_PlayerTexture;

PLAYER g_player;
int g_shootspeed;

bool isEnd;
bool isShoot;

void InitPlayer()
{

	g_PlayerTexture = LoadTexture("rom:/player.tga");

	g_player.pos.x = 0.0f;
	g_player.pos.y = 450.0f;
	g_player.size.x = 140.0f;
	g_player.size.y = 80.0f;
	g_player.HP = g_player.maxHP;
	g_player.shield = g_player.maxShield;
	g_player.isAlive = true;

	g_shootspeed = 0;
	isEnd = false;
	isShoot = false;
}

void UninitPlayer()
{

	UnloadTexture(g_PlayerTexture);

}


void UpdatePlayer()
{
	// ボタン
	if (GetControllerPress(NpadButton::Left::Index))
		g_player.pos.x += -MOVEPOS;
	if (GetControllerPress(NpadButton::Right::Index))
		g_player.pos.x += MOVEPOS;
	if (GetControllerPress(NpadButton::Up::Index))
		g_player.pos.y += -MOVEPOS;
	if (GetControllerPress(NpadButton::Down::Index))
		g_player.pos.y += MOVEPOS;



	// アナログスティック
	Float2 stick;
	stick = GetControllerLeftStick();

	g_player.pos.x += stick.x * MOVEPOS;
	g_player.pos.y -= stick.y * MOVEPOS;



	// タッチスクリーン
	/*if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();
		g_player.pos = touch;
	}*/



	//// 加速度センサー
	//if (GetControllerPress(NpadButton::A::Index))
	//{
	//	Float3 acc;
	//	acc = GetControllerRightAcceleration();

	//	g_player.pos.x += acc.x * 10.0f;
	//	g_player.pos.y += -acc.y * 10.0f;
	//}



	//// ジャイロセンサー
	//if (GetControllerPress(NpadButton::B::Index))
	//{
	//	Float3 angle;
	//	angle = GetControllerRightAngle();

	//	g_player.pos.x = -angle.z * 1000.0f;
	//	g_player.pos.y = angle.x * 1000.0f;
	//}



	//// 振動
	//if (GetControllerPress(NpadButton::Y::Index))
	//{
	//	SetControllerLeftVibration(5);
	//}
	//if (GetControllerPress(NpadButton::X::Index))
	//{
	//	SetControllerRightVibration(5);
	//}

	if (g_player.pos.x < -500.0f + 100.0f)
		g_player.pos.x = -500.0f + 100.0f;

	if (g_player.pos.x > 500.0f - 100.0f)
		g_player.pos.x = 500.0f - 100.0f;

	if (g_player.pos.y < -500.0f + 80.0f)
		g_player.pos.y = -500.0f + 80.0f;

	if (g_player.pos.y > 500.0f)
		g_player.pos.y = 500.0f;

	//弾の発射
	if (GetControllerTrigger(NpadButton::R::Index))
	{
		if (g_player.bullet02Num > 0)
		{
			SetBullet(MakeFloat2(g_player.pos.x, g_player.pos.y - g_player.size.y / 2), MakeFloat2(0.0f, -5.0f), MakeFloat2(64.0f, 196.0f), BULLET_TYPE2);
			g_player.bullet02Num--;
		}
	}

	if (GetControllerTrigger(NpadButton::ZR::Index))
	{
		if (g_player.bullet03Num > 0)
		{
			SetBullet(MakeFloat2(g_player.pos.x, g_player.pos.y - g_player.size.y / 2), MakeFloat2(0.0f, -30.0f), MakeFloat2(32.0f, 128.0f), BULLET_TYPE3);
			g_player.bullet03Num--;
		}
	}

	if (GetControllerTouchScreen() && !isShoot)
	{
		isShoot = true;
		Float2 touch;
		touch = GetControllerTouchScreenPosition();
		if (GetIsTouch(touch, BULLETUSE_SIZE / 2, BULLETUSE_SIZE / 2, BULLETUSE_POSX, BULLETUSE_02_POSY))
		{
			if (g_player.bullet02Num > 0)
			{
				SetBullet(MakeFloat2(g_player.pos.x, g_player.pos.y - g_player.size.y / 2), MakeFloat2(0.0f, -5.0f), MakeFloat2(64.0f, 196.0f), BULLET_TYPE2);
				g_player.bullet02Num--;
			}
		}
		if (GetIsTouch(touch, BULLETUSE_SIZE / 2, BULLETUSE_SIZE / 2, BULLETUSE_POSX, BULLETUSE_03_POSY))
		{
			if (g_player.bullet03Num > 0)
			{
				SetBullet(MakeFloat2(g_player.pos.x, g_player.pos.y - g_player.size.y / 2), MakeFloat2(0.0f, -30.0f), MakeFloat2(32.0f, 128.0f), BULLET_TYPE3);
				g_player.bullet03Num--;
			}
		}
	}
	if (!GetControllerTouchScreen())
	{
		isShoot = false;
	}

	if (g_player.HP <= 0)
	{
		g_player.isAlive = false;
		g_player.HP = 0;
	}
	
	if (!g_player.isAlive && !isEnd)
	{
		//SetExplosion(g_player.pos, g_player.size.x);
		//SetScene(SCENE_RESULT);
		SetExplosion(g_player.pos, g_player.size, EXPLOSION_TYPE4);
		isEnd = true;
		SetFade(FADEMODE_OUT);
	}

	if (g_shootspeed < g_player.shootSpeed)
	{
		g_shootspeed++;
	}
	else
	{
		SetBullet(MakeFloat2(g_player.pos.x, g_player.pos.y - g_player.size.y / 2), MakeFloat2(0.0f, -15.0f), MakeFloat2(16.0f, 32.0f), BULLET_TYPE1);
		g_shootspeed = 0;
	}
}

void DrawPlayer()
{

	SetTexture(g_PlayerTexture);

	if (g_player.isAlive)
	{
		DrawSprite(g_player.pos.x, g_player.pos.y, g_player.size.x, g_player.size.y,
			0.0f, 0.0f, 1.0f, 1.0f,
			MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

PLAYER GetPlayer()
{
	return g_player;
}

void PlayerLifeDecrease(int val)
{
	g_player.HP -= val;
}

void PlayerShieldDecrease(int val)
{
	g_player.shield -= val;
}

void SetPlayerMaxHP(int val)
{
	g_player.maxHP = val;
}

void SetPlayerMaxShield(int val)
{
	g_player.maxShield = val;
}

void SetPlayerShootSpeed(int val)
{
	g_player.shootSpeed = val;
}

void AddPlayerBullet02(void)
{
	g_player.bullet02Num++;
}

void AddPlayerBullet03(void)
{
	g_player.bullet03Num++;
}

void ChangePlayerMoney(int money)
{
	g_player.money += money;
}
