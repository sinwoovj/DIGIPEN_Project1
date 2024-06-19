#include "Enemy.h"

const float RecognizeRange = 50.0f;
bool isReached = false;

void EnemyInit(float x, float y) {

	enemy.coord.x = x;
	enemy.coord.y = y;
	enemy.size = 400;

	enemy.health = 100; // 100 200 300

	enemy.projectileDamage = 5;
	enemy.reachDamage = 10;
	enemy.closeDamage = 10;

	enemy.phase = 1;

	enemy.shape = Circle;

	enemy.isAttack = 0;
	enemy.isHit = 0;
	enemy.isInvincibility = 0;
	enemy.isAlive = 1;
}

void EnemyPhaseSet() {
	switch (++enemy.phase) {
	case 2 :
		enemy.health = 200;

		enemy.projectileDamage = 10;
		enemy.closeDamage = 20;
		break;
	case 3 :
		enemy.health = 300;

		enemy.projectileDamage = 15;
		enemy.closeDamage = 30;
		break;
	case 4 : 
		enemy.isAlive = 0;
		isGameOver = true;
		break;
	}
}

void EnemyAttack() {
	// Condition Check
	// ������ ������ �΋H���� Ȯ�� ���� ����.
	if (RangeTest(enemy.coord, enemy.size, enemy.shape, player.coord, player.size, player.shape)) {
		if (!isReached) {
			player.health -= enemy.closeDamage;
			isReached = true;
		}
	}
	else {
		isReached = false;
	}
	// ������ �÷��̾��� ��ġ�� ���� ���� ���� ������ ��������, �ƴϸ� �������� ������.
	CP_Vector enemyRange;
	enemyRange.x = enemy.coord.x - RecognizeRange;
	enemyRange.y = enemy.coord.y - RecognizeRange;

	if (RangeTest(enemyRange, enemy.size + RecognizeRange * 2, Rect, player.coord, player.size, player.shape)) {
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
