#include "Enemy.h"
#include "EnemyAttack.h"
#include <stdlib.h>
#include <time.h>

const float RecognizeRange = 50.0f;

bool RangeTest(CP_Vector v1, float v1_size, CP_Vector v2, float v2_size) {

}

void EnemyInit(float x, float y) {
	enemy.coord.x = x;
	enemy.coord.y = y;
	enemy.size = 400;
	enemy.health = 100; // 100 200 300
	enemy.closeDamage = 5; // 5 10 15
	enemy.phase = 1;
	enemy.isAttack = 0;
	enemy.isHit = 0;
	enemy.isInvincibility = 0;
	enemy.isAlive = 1;
}

void EnemyAttack() {
	// Condition Check
	// ������ ������ �΋H���� Ȯ�� ���� ����.
	if (RangeTest(enemy.coord, enemy.size, player.coord, player.size)) {
		player.health -= enemy.closeDamage;
	}
	// ������ �÷��̾��� ��ġ�� ���� ���� ���� ������ ��������, �ƴϸ� �������� ������.
	CP_Vector enemyRange;
	enemyRange.x = enemy.coord.x - RecognizeRange;
	enemyRange.y = enemy.coord.y - RecognizeRange;

	if (RangeTest(enemyRange, enemy.size + RecognizeRange * 2, player.coord, player.size)) {
		EnemyCloseAttack();
	}
	EnemyRandomAttack();
}

void EnemyRandomAttack()
{
	srand(time(NULL));
	int random = 0; // ������ ���� ����
	random = rand() % (enemy.phase * 3); // ���� ����

	switch (random) {
		case 1 :
			EnemyProjectileRandomAttack1();
			break;
		case 2:
			EnemyProjectileRandomAttack2();
			break;
		case 3:
			EnemyProjectileRandomAttack3();
			break;
		case 4:
			EnemyCloseAttack1();
			break;
		case 5:
			EnemyCloseAttack2();
			break;
		case 6:
			EnemyCloseAttack3();
			break;
		case 7:
			EnemyPatternAttack1();
			break;
		case 8:
			EnemyPatternAttack2();
			break;
		case 9:
			EnemyPatternAttack3();
			break;
	}
}
