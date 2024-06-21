#include "EnemyAttack.h"
#include "Player.h"
#include "cprocessing.h"
#include "Enemy.h"
#include "Standard.h"

const float WindowWidthHalf = 960; // windowWinth / 2
const float WindowHeightHalf = 540; // windowHeight / 2

void SignDanagerZone(float x, float y, float w, float h)
{
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 40));
	CP_Graphics_DrawRect(x, y, w, h);
}

// �⺻������ ���������� 3�ʿ��� 1�� ���̿� ���������� ���� ������ŭ ǥ���ϰ� �����Ѵ�.
// �׳� ��,���簢���� 
void EnemyCloseAttack1() // �ѹ���
{
	// �÷��̾� ��ġ�� �������� ������ �����ؼ� ������
	// x�� ���� windowWidth / 2�� �������� ū�� ������ ������ �״��� y��
	if (currentEnemyFrame2 <= FRAME) {
		if (player.coord.x >= WindowWidthHalf)
		{
			if (player.coord.y >= WindowHeightHalf)  EnemyCloseAttackNum = 1;
			else EnemyCloseAttackNum = 2;
		}
		else {
			if (player.coord.y >= WindowHeightHalf) EnemyCloseAttackNum = 3;
			else EnemyCloseAttackNum = 4;
		}
	}
	
	switch (EnemyCloseAttackNum)
	{
		case 1 :
			SignDanagerZone(WindowWidthHalf, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
		case 2 :
			SignDanagerZone(WindowWidthHalf, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
		case 3 :
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
		case 4 :
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
	}
}
void EnemyCloseAttack2() // ���� ����
{
	// x�� ���� ũ�� ��ŭ�� ��ǥ�� �ش��ϴ��� �׽�Ʈ�ϰ� ������ ����, �ƴϸ� �������� �Ѵ�.
	if (currentEnemyFrame2 <= FRAME) {
		if (player.coord.x >= WindowWidthHalf - enemy.size / 2 && player.coord.x <= WindowWidthHalf + enemy.size) EnemyCloseAttackNum = 5;
		else EnemyCloseAttackNum = 6;
	}
	switch (EnemyCloseAttackNum)
	{
		case 5:

			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y + enemy.size, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
			break;
		case 6:
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
			SignDanagerZone(enemy.range.x + enemy.size, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
			break;
	}
}
void EnemyCloseAttack3() // ������
{
	// ������
	// ǥ�� n�ʰ�
	EnemyCloseAttackNum = 7;
	SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.size + enemy.recognizeRange * 2);
	// ���� ����
}

bool isPlayerIncludeRange()
{
	switch (EnemyCloseAttackNum)
	{
		case 1:
			if (player.coord.x >= WindowWidthHalf && player.coord.y >= WindowHeightHalf)
				return 1;
			break;
		case 2:
			if (player.coord.x >= WindowWidthHalf && player.coord.y < WindowHeightHalf)
				return 1;
			break;
		case 3:
			if (player.coord.x < WindowWidthHalf && player.coord.y >= WindowHeightHalf)
				return 1;
			break;
		 case 4:
			if (player.coord.x < WindowWidthHalf && player.coord.y < WindowHeightHalf)
				return 1;
			break;
		case 5:
			if (player.coord.x >= WindowWidthHalf - enemy.size / 2 && player.coord.x <= WindowWidthHalf + enemy.size)
				return 1;
			break;
		case 6:
			if (player.coord.x < WindowWidthHalf - enemy.size / 2 || player.coord.x > WindowWidthHalf + enemy.size)
				return 1;
			break;
		case 7:
			if (isPlayerInsideRange)
				return 1;
			break;
	}
	return 0;
}

void EnemyProjectileRandomAttack1() // ����
{
	float degree = 0.f;
	float velocity = 10.0f;
	int direction = 0;
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		CreateEnemyProjectile(WindowWidthHalf + (enemy.size / 2.0) * cosf(CP_Math_Radians(degree)), WindowHeightHalf + (enemy.size / 2.0) * sinf(CP_Math_Radians(degree)), velocity, direction);
		direction++;
		if (direction == 8) direction = 0;
		degree -= 45;
		if (degree == -405) degree = 0;
	}
	/*degree -= 90;
	CreateEnemyProjectile(WindowWidthHalf + 50 * (float)cos(degree), WindowHeightHalf + 50 * (float)sin(degree), velocity, 2);*/
}
void EnemyProjectileRandomAttack2() // ���� ����
{
	float degree = 0.f;
	float velocity = 10.0f;
	int direction = 0;
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		CreateEnemyProjectile(WindowWidthHalf + (enemy.size / 2.0) * cosf(CP_Math_Radians(degree)), WindowHeightHalf + (enemy.size / 2.0) * sinf(CP_Math_Radians(degree)), velocity, direction);
		direction += 2;
		if (direction == 8) direction = 0;
		degree -= 90;
		if (degree == -450) degree = 0;
	}
}
void EnemyProjectileRandomAttack3() // ����
{
	float degree = 0.f;
	float velocity = 10.0f;
	int direction = 0;
	for (int i = 0; i < 4; i++)
	{
		CreateEnemyProjectile_2(WindowWidthHalf + (enemy.size / 2.0) * cosf(CP_Math_Radians(degree)), WindowHeightHalf + (enemy.size / 2.0) * sinf(CP_Math_Radians(degree)), velocity, direction);
		direction += 2;
		if (direction == 4) direction = 0;
		degree -= 90;
		if (degree == -450) degree = 0;
	}
}

void EnemyPatternAttack1()
{

}
void EnemyPatternAttack2()
{

}
void EnemyPatternAttack3()
{

}
