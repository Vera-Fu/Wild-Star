#pragma once
#ifndef PROGRESS_H_
#define PROGRESS_H_

#define PROGRESS_SIZEX 50.0f
#define HPPROGRESS_POSX -650.0f
#define SHIELDPROGRESS_POSX -750.0f

void InitProgress();
void UninitProgress();
void UpdateProgress();
void DrawProgress();

#endif // !PROGRESS_H_