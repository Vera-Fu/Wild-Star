#pragma once
#ifndef LEVELBG_H_
#define LEVELBG_H_

#define ROLL_SPD 4.0f

#define MENUBTN_SIZE 64.0f
#define MENUBTN_POSX 460.0f
#define MENUBTN_POSY -490.0f


typedef enum {
	BTN_CONTINUE = 0,
	BTN_BATTLEQUIT
}BATTLEMENUBTN;

void InitLevelBG();
void UninitLevelBG();
void UpdateLevelBG();
void DrawLevelBG();

BATTLEMENUBTN GetBMBTN(void);

#endif // !LEVELBG_H_