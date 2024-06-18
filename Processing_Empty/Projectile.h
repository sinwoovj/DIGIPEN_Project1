#pragma once
#include "cprocessing.h"
#include "stdbool.h"
#define MAX_PROJECTILES 100

typedef struct Projectile
{
	//����ü ������
	float size;

	//����ü ��ġ (ó�� ��ġ�� �÷��̾� ��ġ�� ����)
	float position_x;
	float position_y;

	//����ü �ӵ�
	float velocity;

	int active;
}Proj;
Proj projectile[MAX_PROJECTILES];

void Create_Projectile(float x, float y, float velocity);
void Draw_Projectile();
void Draw_RightProjectile();
bool Right;