#pragma once
#include "cprocessing.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Rect
{
	float x;
	float y;
	float size;
	CP_Color color;
}R;

R Rect[2];
int cnt, aoc, CollisionSize;
float velocity;
float distance;
void Draw();
void Key();
void CountText();
void CollisionBox();