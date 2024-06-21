#pragma once
#define MAX_ENEMYPROJECTIES 50
#include "cprocessing.h"
#include "Standard.h"

typedef struct EnemyProjectile
{
	//����ü ������
	float size;

	//����ü ��ġ (ó�� ��ġ�� �÷��̾� ��ġ�� ����)
	CP_Vector position;
	//����ü �ӵ�
	float velocity;
	Shape shape;

	int active;
	int direction; // 0: right, 1: left, 2: up, 3: down
}EnemyProject;
EnemyProject enemyProjectile[MAX_ENEMYPROJECTIES];
EnemyProject enemyProjectile_2[MAX_ENEMYPROJECTIES];


void CreateEnemyProjectile(float x, float y, float velocity, int direction); // ���� ���� ����
void CreateEnemyProjectile_2(float x, float y, float velocity, int direction); // ����
void DrawEnemyProjectile(); // ���� ���� ����
void DrawEnemyProjectile_2(); // ����