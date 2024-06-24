#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Enemy.h"
#include "UI.h"
#include "Standard.h"
#include "EnemyAttack.h"
#include "Calculate.h"
#include "Image.h"
#include "Player.h"
#include "Sound.h"
#include "EnemyProjectile.h"


bool isReached;
bool isRecognize;
bool isCloseAttack;

int enemyAttackRandom;
int enemyCloseAttackRandom;
int enemyRandomPatternNum;

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
	enemy.patternDamage = 10;

	enemy.phase = 1;
	enemy.maxHP = 100;
	enemy.isPhase1Full = true;

	enemy.shape = Circle;

	enemy.isAttack = 0;
	enemy.isHit = 0;
	enemy.isInvincibility = 0;
	enemy.isAlive = 1;

	enemy.closeAttackNum = 0;
	enemy.patternAttackNum = 0;

	enemy.patternRandomNum = 0;

	enemy.recognizeRange = 100.0f;
	enemy.closeAttackCoolTime = FRAME * 2;

	// enemy.c
	isReached = false;
	isRecognize = false;
	isCloseAttack = false;

	enemyAttackRandom;
	enemyCloseAttackRandom;
	enemyRandomPatternNum;

	// enemy.h
	isEnemyCloseAttack = false;
	isEnemyProjectailAttack = false;
	isEnemyPatternAttack = false;
	isPlayerInsideRange = false;
	isCloseAttackCool = false;
	isPatternAttackCool = false;

	currentPhaseTerm = FRAME * 3;
	currentPatternPhaseTerm = FRAME * 5;

	currentEnemyFrame1 = 0;
	currentEnemyFrame2 = 0;
	currentEnemyFrame3 = 0;

	EnemyCloseAttackNum = 0;
	EnemyPatternAttackNum = 0;

	dangerZoneOpacity = 0;
	dangerZonePatternOpacity = 0;

	patternInterval = (FRAME * 2);
	punchFrame = 0;
	punchState = 0;
	isPunchAnim = false;
	EnemyCheckPatternFrame = 0;
	EnemyCheckPatternFrameLimit = 0;

	iscurrentEnemyFrame2 = false;
	iscurrentEnemyFrame3 = false;
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
	if (currentEnemyFrame2 >= currentPhaseTerm + FRAME) {
		currentEnemyFrame2 = 0;
		iscurrentEnemyFrame2 = false;
		dangerZoneOpacity = 0;
		isCloseAttackCool = false;
		return true;
	}
	if (!iscurrentEnemyFrame2) {
		if (currentEnemyFrame2 >= currentPhaseTerm) {
			iscurrentEnemyFrame2 = true;
			isCloseAttackCool = true;
			if (isPlayerIncludeRange())
			{
				player.health -= enemy.closeDamage;
				CP_Sound_PlayAdvanced(playerHurt, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
			}
		}
	}
	dangerZoneOpacity = (int)((currentEnemyFrame2 * MaxDangerZoneOpacity) / currentPhaseTerm);
	currentEnemyFrame2++;
	return false;
}
bool EnemyFrameCheck3() {
	if (currentEnemyFrame3 >= currentPatternPhaseTerm + patternInterval) {
		currentEnemyFrame3 = 0;
		iscurrentEnemyFrame3 = false;
		dangerZonePatternOpacity = 0;
		isPatternAttackCool = false;
		return true;
	}
	if (!iscurrentEnemyFrame3) {
		if (currentEnemyFrame3 >= currentPatternPhaseTerm) {
			iscurrentEnemyFrame3 = true;
			isPatternAttackCool = true;
			if (isPlayerIncludePatternRange())
				player.health -= enemy.patternDamage;
		}
		if (currentEnemyFrame3 >= currentPatternPhaseTerm && (EnemyPatternAttackNum == 9 || EnemyPatternAttackNum == 10)) {
			isPunchAnim = true;
		}
	}
	// isPatternAttackCool == 1 -> alpha 0
	dangerZonePatternOpacity = isPatternAttackCool ? 0 : (int)(((currentEnemyFrame3 / 2) * MaxDangerZoneOpacity) / currentPatternPhaseTerm);
	currentEnemyFrame3++;
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
		CP_Sound_PlayAdvanced(changePhase, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
		enemy.health = 20;

		enemy.projectileDamage = 10;
		enemy.closeDamage += 10;
		enemy.reachDamage += 10;
		enemy.patternDamage = 15;
		enemy.closeAttackCoolTime -= FRAME / 2;
		currentPhaseTerm -= FRAME;
		currentPatternPhaseTerm -= FRAME;
		enemy.recognizeRange += 50;
		break;

	case 3 :
		CP_Sound_PlayAdvanced(changePhase, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
		enemy.health = 20;

		enemy.projectileDamage = 15;
		enemy.closeDamage += 10;
		enemy.reachDamage += 10;
		enemy.patternDamage = 20;
		enemy.closeAttackCoolTime -= FRAME / 2;
		currentPhaseTerm -= FRAME;
		currentPatternPhaseTerm -= FRAME;
		enemy.recognizeRange += 50;
		break;
	case 4 : 
		player.isAlive = 0;
		enemy.isAlive = 0;
		break;
	default:
		enemy.phase = 4;
	}
}

void EnemyDraw(float BossLocationX, float BossLocationY) {
	if(enemy.phase == 3)
		CP_Image_Draw(BossFace_Phase3, BossLocationX, BossLocationY, enemy.size, enemy.size, 255); //Draw BG
	else
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
	// 보스와 완전히 부딪히면 확정 딜을 입음.

	if (RangeTest(enemy.coord, enemy.size, enemy.shape, player.coord, player.size, player.shape, 0, 0)) {
		if (InvincibleTime()) {
			player.health -= enemy.reachDamage;
			CP_Sound_PlayAdvanced(playerHurt, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
		}
	}
	// 보스와 플레이어의 위치가 일정 범위 내로 가까우면 근접공격, 아니면 랜덤으로 공격함.
	CP_Vector enemyRange;
	enemyRange.x = enemy.range.x - enemy.recognizeRange;
	enemyRange.y = enemy.range.y - enemy.recognizeRange;
	CP_Vector playerRange;
	playerRange.x = player.coord.x + player.size / 2;
	playerRange.y = player.coord.y + player.size / 2;
	
	if (EnemyFrameCheck1())
		EnemyRandomAttack();
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		if(RangeTest(enemyProjectile[i].position, enemyProjectile[i].size, enemyProjectile[i].shape, playerRange, player.size, player.shape, 0, 0))
		{
			enemyProjectile[i].position.x = 0;
			enemyProjectile[i].position.y = 0;
			enemyProjectile[i].active = 0;
			player.health -= enemy.projectileDamage;
			CP_Sound_PlayAdvanced(playerHurt, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
		}
		if (RangeTest(enemyProjectile_2[i].position, enemyProjectile_2[i].size, enemyProjectile_2[i].shape, playerRange, player.size, player.shape, 0, 0))
		{
			enemyProjectile_2[i].position.x = 0;
			enemyProjectile_2[i].position.y = 0;
			enemyProjectile_2[i].active = 0;
			player.health -= enemy.projectileDamage;
			CP_Sound_PlayAdvanced(playerHurt, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_1);
		}
	}
	if (RangeTest(enemyRange, enemy.size + enemy.recognizeRange * 2, Square, player.coord , player.size, player.shape, 0, 0))
	{
		isPlayerInsideRange = true;
		if (!isRecognize)
		{
			srand((unsigned int)(time(NULL)));
			enemy.closeAttackNum = (rand() % 3) + 1;
			isRecognize = true;
		}
	}
	else {
		isPlayerInsideRange = false;
	}
	if (isRecognize)
	{
		if (EnemyFrameCheck2())
		{
			isRecognize = false;
			enemy.closeAttackNum = 0; // 범위 내 없음
		}
		else
		{
			EnemyRandomCloseAttack();
		}
	}

	// return 1 means the current pattern ends 
	if (EnemyFrameCheck3())
	{
		srand((unsigned int)(time(NULL)));
		// resetting the current pattern
		enemyRandomPatternNum = enemy.phase < 2 ? 1 : (rand() % 3) + 1;
		//enemyRandomPatternNum = enemy.phase == 2 ? 1 : enemy.phase == 3 ? (rand() % 3) + 1 : (rand() % 5) + 1;
		enemy.patternRandomNum = (rand() % 2) + 1; // 1 > 수직 / 2 > 수평
		enemy.patternAttackNum = 0;
	}
	else {
		EnemyRandomPatternAttack();
	}

	if (isPunchAnim)
		EnemyCheckPatternAnim();
}

void EnemyRandomCloseAttack()
{
	switch (enemy.closeAttackNum) {
	case 1:
		// 한방향
		EnemyCloseAttack1();
		break;
	case 2:
		// 수직, 수평
		EnemyCloseAttack2();
		break;
	case 3:
		// 전방향
		EnemyCloseAttack3();
		break;
	}
}

void EnemyRandomAttack()
{
	srand((unsigned int)(time(NULL)));

	int random1 = 0; // 정수형 변수 선언

	random1 = rand() % 3 + 1; // 난수 생성
	
	switch (random1)
	{
		case 1:
			EnemyProjectileRandomAttack1(); // 원형
			break;
		case 2:
			EnemyProjectileRandomAttack2(); // 수직, 수평
			break;
		case 3:
			EnemyProjectileRandomAttack3(); // 유도
			break;
	}
}

void EnemyRandomPatternAttack()
{
	EnemyPatternAttack3();
		/*
	switch (enemyRandomPatternNum)
	{
		case 1:
			EnemyPatternAttack1(); // 맵 1/4
			break;
		case 2:
			EnemyPatternAttack2(); // 맵 1/2
			break;
		case 3:
			EnemyPatternAttack3(); // 체크
			break;
		case 4:
			EnemyPatternAttack4(); // 가로 또는 세로로 8등분 하여 순차, 광역 공격
			break;
		case 5:
			EnemyPatternAttack5(); // 체크 순차,광역 공격
			break;
	}*/
}