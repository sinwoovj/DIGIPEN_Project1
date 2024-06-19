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

	phaseTerm[0] = 30 * 6;
	phaseTerm[1] = 30 * 4;
	phaseTerm[2] = 30 * 2;

	currentPhaseTerm = phaseTerm[0];
	currentEnemyFrame = 0;
}

bool EnemyFrameCheck() {
	if (currentEnemyFrame == currentPhaseTerm) {
		currentEnemyFrame = 0;
		return true;
	}
	currentEnemyFrame++;
	return false;
}

void EnemyCheck()
{
	if (enemy.health <= 0)
		EnemyPhaseSet();
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
	currentPhaseTerm = phaseTerm[enemy.phase - 2];
}

void EnemyDraw(float BossLocationX, float BossLocationY) {
	CP_Image_Draw(BossFace, BossLocationX, BossLocationY, enemy.size, enemy.size, 255); //Draw BG
}

void EnemyAttack() {
	// Condition Check
	// ������ ������ �΋H���� Ȯ�� ���� ����.
	if (RangeTest(enemy.coord, enemy.size, enemy.shape, player.coord, player.size, player.shape, 0, 0)) {
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
	if (EnemyFrameCheck()) {
		if (RangeTest(enemyRange, enemy.size + RecognizeRange * 2, Square, player.coord, player.size, player.shape, 0, 0))
			EnemyRandomAttack(true);
		else
			EnemyRandomAttack(false);
	}
}

void EnemyRandomAttack(bool isNear)
{
	srand(time(NULL));

	int random1 = 0, random2 = 0, random3 = 0; // ������ ���� ����

	random1 = isNear ? (rand() % 3) + 1 : 0;

	random2 = rand() % 3 + 1; // ���� ����
	
	random3 = (rand() % (enemy.phase == 2 ? 2 : 3)) + 1; // ���� ����

	switch (random1) {
		case 0:
			break;
		case 1:
			EnemyCloseAttack1(); //�ѹ���
			break;
		case 2:
			EnemyCloseAttack2(); //����,����
			break;
		case 3:
			EnemyCloseAttack3(); //������
			break;
	}

	switch (random2)
	{
		case 1:
			EnemyProjectileRandomAttack1(); // ����
			break;
		case 2:
			EnemyProjectileRandomAttack2(); // ����, ����
			break;
		case 3:
			EnemyProjectileRandomAttack3(); // ����
			break;
	}
	if (enemy.phase >= 2) {
		switch (random3)
		{
		case 1:
			EnemyPatternAttack1(); // �� 1/4
			break;
		case 2:
			EnemyPatternAttack2(); // �� 1/2
			break;
		case 3:
			EnemyPatternAttack3(); // üũ
			break;
		}
	}
}
