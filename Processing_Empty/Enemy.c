#include "Enemy.h"
#include "UI.h"
#include "Standard.h"

const float RecognizeRange = 50.0f;
bool isReached = false;
bool isRecognize = false;
bool isCloseAttack = false;

int enemyAttackRandom = 0;
int enemyCloseAttackRandom = 0;

void EnemyInit(float x, float y) {

	enemy.coord.x = x;
	enemy.coord.y = y;
	enemy.size = 400;
	enemy.range.x = x - enemy.size / 2;
	enemy.range.y = y - enemy.size / 2;

	enemy.health = 10; // 100 200 300

	enemy.projectileDamage = 5;
	enemy.reachDamage = 10;
	enemy.closeDamage = 10;

	enemy.phase = 1;
	enemy.maxHP = 100;
	enemy.isPhase1Full = true;

	enemy.shape = Circle;

	enemy.isAttack = 0;
	enemy.isHit = 0;
	enemy.isInvincibility = 0;
	enemy.isAlive = 1;

	enemy.closeAttackNum = 0;
	enemy.recognizeRange = 100.0f;
	enemy.closeAttackCoolTime = FRAME * 3;

	currentPhaseTerm = FRAME * 6;
	currentEnemyFrame1 = 0;
	currentEnemyFrame2 = 0;
}

bool EnemyFrameCheck1() {
	if (currentEnemyFrame1 >= currentPhaseTerm) {
		currentEnemyFrame1 = 0;
		return true;
	}
	currentEnemyFrame1++;
	return false;
}
bool EnemyFrameCheck2() {
	if (currentEnemyFrame2 >= currentPhaseTerm) {
		currentEnemyFrame2 = 0;
		return true;
	}
	currentEnemyFrame2++;
	return false;
}

void EnemyCheck()
{
	if (enemy.health <= 0)
		EnemyPhaseSet();
}


void EnemyPhaseSet() {
	switch (++enemy.phase)
	{
	case 2:
		enemy.health = 10;

		enemy.projectileDamage = 10;
		enemy.closeDamage = 20;

		break;

	case 3 :
		enemy.health = 10;

		enemy.projectileDamage = 15;
		enemy.closeDamage = 30;
		break;

	case 4 : 
		enemy.isAlive = 0;
		isGameOver = true;
		break;
	}
	enemy.recognizeRange += 50;
	enemy.closeAttackCoolTime -= FRAME;
	currentPhaseTerm -= FRAME * 2;
}

void EnemyDraw(float BossLocationX, float BossLocationY) {
	CP_Image_Draw(BossFace, BossLocationX, BossLocationY, enemy.size, enemy.size, 255); //Draw BG
}

int invincibleCount = 0;
const int invincibleLimit = 30;
bool InvincibleTime()
{
	if (++invincibleCount == invincibleLimit)
	{
		invincibleCount = 0;
		return true;
	}
	else
		return false;
}
void EnemyAttack() {
	// Condition Check
	// ������ ������ �΋H���� Ȯ�� ���� ����.

	if (RangeTest(enemy.coord, enemy.size, enemy.shape, player.coord, player.size, player.shape, 0, 0)) {
		if (InvincibleTime()) {
			player.health -= enemy.closeDamage;
		}
	}
	// ������ �÷��̾��� ��ġ�� ���� ���� ���� ������ ��������, �ƴϸ� �������� ������.
	CP_Vector enemyRange;
	enemyRange.x = enemy.range.x - enemy.recognizeRange;
	enemyRange.y = enemy.range.y - enemy.recognizeRange;

	if (EnemyFrameCheck1())
		EnemyRandomAttack();
	if (RangeTest(enemyRange, enemy.size + enemy.recognizeRange * 2, Square, player.coord, player.size, player.shape, 0, 0))
	{
		if (!isRecognize)
		{
			srand(time(NULL));
			enemy.closeAttackNum = (rand() % 3) + 1;
			isRecognize = true;
		}
	}
	if (isRecognize)
	{
		if (EnemyFrameCheck2())
		{
			isRecognize = false;
			enemy.closeAttackNum = 0; // ���� �� ����
		}
		else
		{
			EnemyRandomCloseAttack();
		}
	}
}

void EnemyRandomCloseAttack()
{
	switch (enemy.closeAttackNum) {
	case 1:
		// �ѹ���
		EnemyCloseAttack1();
		break;
	case 2:
		// ����, ����
		EnemyCloseAttack2();
		break;
	case 3:
		// ������
		EnemyCloseAttack3();
		break;
	}
}

void EnemyRandomAttack()
{
	srand(time(NULL));

	int random1 = 0, random2 = 0; // ������ ���� ����

	random1 = rand() % 3 + 1; // ���� ����
	
	random2 = (rand() % (enemy.phase == 2 ? 2 : 3)) + 1; // ���� ����
	switch (random1)
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
		switch (random2)
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