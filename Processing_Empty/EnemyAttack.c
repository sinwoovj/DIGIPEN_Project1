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

// 기본적으로 근접공격은 3초에서 1초 사이에 빨간색으로 공격 범위만큼 표시하고 공격한다.
// 그냥 정,직사각형을 
void EnemyCloseAttack1() // 한방향
{
	// 플레이어 위치를 기준으로 방향을 결정해서 공격함
	// x를 먼저 windowWidth / 2를 기준으로 큰지 작은지 나누고 그다음 y순
	//if (currentEnemyFrame2 <= enemy.phase * )
	if (player.coord.x >= WindowWidthHalf)
	{
		if (player.coord.y >= WindowHeightHalf) 
		{
			// RightBottom
			// 표시 n초간
			SignDanagerZone(WindowWidthHalf, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// 이후 공격
		}
		else 
		{
			// RightTop
			// 표시 n초간
			SignDanagerZone(WindowWidthHalf, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// 이후 공격
		}
	}
	else {
		if (player.coord.y >= WindowHeightHalf) 
		{
			// LeftBottom
			// 표시 n초간
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// 이후 공격
		}
		else 
		{
			// LeftTop
			// 표시 n초간
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			// 이후 공격
		}
	}
	//switch()
}
void EnemyCloseAttack2() // 수직 수평
{
	// x가 보스 크기 만큼의 좌표에 해당하는지 테스트하고 맞으면 수평, 아니면 수직으로 한다.
	if (player.coord.x >= WindowWidthHalf - enemy.size / 2 && player.coord.x <= WindowWidthHalf + enemy.size) // 수평
	{
		// 표시 n초간
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y + enemy.size, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
		// 이후 공격
	}
	else // 수직
	{
		// 표시 n초간
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
		SignDanagerZone(enemy.range.x + enemy.size, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
		// 이후 공격
	}
}
void EnemyCloseAttack3() // 전방향
{
	// 전방향
	// 표시 n초간
	SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.size + enemy.recognizeRange * 2);
	// 이후 공격
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
