#pragma once
#include "cprocessing.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX_PROJECTILES 100

typedef struct Rect
{
	float x;
	float y;
	float size;
	CP_Color color;
}R;
R Rect;
int aoc;

typedef struct Projectile
{
	//����ü ������
	float projectile_size;

	//����ü ��ġ (ó�� ��ġ�� �÷��̾� ��ġ�� ����)
	float projectile_position_x;
	float projectile_position_y;

	//����ü �ӵ�
	float projectile_velocity;

	int active;
}Proj;
Proj test[MAX_PROJECTILES];

void Draw();
void Key();

void Create_Projectile(float x, float y, float velocity);

void Roughly_game_init(void);
void Roughly_game_update(void);
void Roughly_game_exit(void);

