//---------------------------------------------------------------
//game.cpp
//
//												çÏê¨é“ÅFFU YIZHI
//												çÏê¨ì˙ÅF2021/6/25
//---------------------------------------------------------------

#include "main.h"
#include "game.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "level.h"
#include "levelbg.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemybullet.h"
#include "explosion.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "progress.h"
#include "UI.h"


void InitGame()
{
	ShowUI(NOTHINGUI);
	InitLevel();
	InitPlayer();
	InitBullet();
	InitEnemy();
	InitEnemyBullet();
	InitExplosion();
	InitScore();
	InitProgress();
	//StopBGM();
	//PlayBGM(STRM_LEVEL_01_BATTLE_BGM);
	//SetVolumeBGM(0, 0);
	//SetVolumeBGM(1.0, 120);
}


void UninitGame()
{
	UninitLevel();
	UninitPlayer();
	UninitBullet();
	UninitEnemy();
	UninitEnemyBullet();
	UninitExplosion();
	//UninitScore();
	UninitProgress();

}


void UpdateGame()
{
	UpdateLevel();
	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
	UpdateEnemyBullet();
	UpdateExplosion();
	UpdateScore();
	UpdateProgress();
	/*if (GetControllerTrigger(NpadButton::L::Index))
	{
		//SetScene(SCENE_RESULT);
		SetFade(FADEMODE_OUT);
	}*/
}


void DrawGame()
{
	DrawLevel();
	DrawPlayer();
	DrawBullet();
	DrawEnemy();
	DrawEnemyBullet();
	DrawExplosion();
	DrawScore();
	DrawProgress();
}