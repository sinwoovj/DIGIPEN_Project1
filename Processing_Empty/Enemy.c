#include "Enemy.h"
#include "EnemyAttack.h"
#include <stdlib.h>
#include <time.h>

const float RecognizeRange = 100.0f;

void EnemyAttack(Enemy enemy_, Player player) {
	// Condition Check
	// 보스와 플레이어의 위치가 가까우면 근접공격, 아니면 랜덤으로 공격함.

	EnemyRandomAttack(enemy_);
}

void EnemyRandomAttack(Enemy enemy_)
{
	srand(time(NULL));
	int random = 0; // 정수형 변수 선언
	random = rand() % (enemy_.phase * 3); // 난수 생성

}
