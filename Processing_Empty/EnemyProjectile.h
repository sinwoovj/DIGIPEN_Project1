#pragma once
#define MAX_ENEMYPROJECTIES 100
#include "cprocessing.h"
#include "Standard.h"

typedef struct EnemyProjectile
{
	//����ü ������
	float size;

	//����ü ��ġ (ó�� ��ġ�� �÷��̾� ��ġ�� ����)
	float position_x;
	float position_y;

	//����ü �ӵ�
	float velocity;
	Shape shape;

	int active;
	int direction; // 0: right, 1: left, 2: up, 3: down
}EnemyProject;
EnemyProject enemyProjectile[MAX_ENEMYPROJECTIES];


void CreateEnemyProjectile(float x, float y, float velocity, int direction);
void DrawEnemyProjectile();