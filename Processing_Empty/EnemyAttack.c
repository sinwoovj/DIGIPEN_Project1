#include "EnemyAttack.h"
#include "Player.h"
#include "cprocessing.h"
#include "Enemy.h"

const float WindowWidthHalf = 960; // windowWinth / 2
const float WindowHeightHalf = 540; // windowHeight / 2

void SignDanagerZone(float x, float y, float w, float h)
{
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 40));
	CP_Graphics_DrawRect(x, y, w, h);
}

int EnemyCloseAttackNum1;
int EnemyCloseAttackNum2;

// �⺻������ ���������� 3�ʿ��� 1�� ���̿� ���������� ���� ������ŭ ǥ���ϰ� �����Ѵ�.
// �׳� ��,���簢���� 
void EnemyCloseAttack1() // �ѹ���
{
	// �÷��̾� ��ġ�� �������� ������ �����ؼ� ������
	// x�� ���� windowWidth / 2�� �������� ū�� ������ ������ �״��� y��
	//if (currentEnemyFrame2 <= enemy.phase * )
	if (player.coord.x >= WindowWidthHalf)
	{
		if (player.coord.y >= WindowHeightHalf) 
		{
			// RightBottom
			// ǥ�� n�ʰ�
			SignDanagerZone(WindowWidthHalf, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// ���� ����
		}
		else 
		{
			// RightTop
			// ǥ�� n�ʰ�
			SignDanagerZone(WindowWidthHalf, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// ���� ����
		}
	}
	else {
		if (player.coord.y >= WindowHeightHalf) 
		{
			// LeftBottom
			// ǥ�� n�ʰ�
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// ���� ����
		}
		else 
		{
			// LeftTop
			// ǥ�� n�ʰ�
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// ���� ����
		}
	}
	//switch()
}
void EnemyCloseAttack2() // ���� ����
{
	// x�� ���� ũ�� ��ŭ�� ��ǥ�� �ش��ϴ��� �׽�Ʈ�ϰ� ������ ����, �ƴϸ� �������� �Ѵ�.
	if (player.coord.x >= WindowWidthHalf - enemy.size / 2 && player.coord.x <= WindowWidthHalf + enemy.size) // ����
	{
		// ǥ�� n�ʰ�
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y + enemy.size, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
		// ���� ����
	}
	else // ����
	{
		// ǥ�� n�ʰ�
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
		SignDanagerZone(enemy.range.x + enemy.size, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
		// ���� ����
	}
}
void EnemyCloseAttack3() // ������
{
	// ������
	// ǥ�� n�ʰ�
	SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.size + enemy.recognizeRange * 2);
	// ���� ����
}


void EnemyProjectileRandomAttack1()
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
void EnemyProjectileRandomAttack2()
{
	
}
void EnemyProjectileRandomAttack3()
{

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
