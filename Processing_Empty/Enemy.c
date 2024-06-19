#include "Enemy.h"

const float RecognizeRange = 50.0f;

bool RangeTest(CP_Vector v1, float v1_size, CP_Vector v2, float v2_size) { // v1이 base, v2가 target
	bool res = false;
	
	CP_Vector coord[4];

	coord[0] = v2;

	coord[1].x = v2.x + v2_size;
	coord[1].y = v2.y;

	coord[2].x = v2.x;
	coord[2].y = v2.y + v2_size;

	coord[3].x = v2.x + v2_size;
	coord[3].y = v2.y + v2_size;

	for (int i = 0; i < 4; i++) {
		if (coord[i].x >= v1.x && coord[i].x <= v1.x + v1_size &&
			coord[i].y >= v1.y && coord[i].y <= v1.y + v1_size)
			res = true;
	}

	return res;
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
	// 보스와 완전히 부딫히면 확정 딜을 입음.
	if (RangeTest(enemy.coord, enemy.size, player.coord, player.size)) {
		player.health -= enemy.closeDamage;
	}
	// 보스와 플레이어의 위치가 일정 범위 내로 가까우면 근접공격, 아니면 랜덤으로 공격함.
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
	int random = 0; // 정수형 변수 선언
	random = rand() % (enemy.phase * 3); // 난수 생성

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
