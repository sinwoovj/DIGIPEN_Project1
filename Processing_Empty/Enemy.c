#include "Enemy.h"
#include "EnemyAttack.h"
#include <stdlib.h>
#include <time.h>

const float RecognizeRange = 100.0f;

void EnemyAttack(Enemy enemy_, Player player) {
	// Condition Check
	// ������ �÷��̾��� ��ġ�� ������ ��������, �ƴϸ� �������� ������.

	EnemyRandomAttack(enemy_);
}

void EnemyRandomAttack(Enemy enemy_)
{
	srand(time(NULL));
	int random = 0; // ������ ���� ����
	random = rand() % (enemy_.phase * 3); // ���� ����

}
