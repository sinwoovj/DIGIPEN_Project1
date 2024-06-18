#pragma once
#include "cprocessing.h"
#include "Projectile.h"
#include<stdio.h>

typedef struct Rect
{
	float x;
	float y;
	float size;
	CP_Color color;
}R;
R Rect;
int aoc;

void Draw();
void Key();

void Roughly_game_init(void);
void Roughly_game_update(void);
void Roughly_game_exit(void);

