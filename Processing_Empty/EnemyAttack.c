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
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, dangerZoneOpacity >= MaxDangerZoneOpacity ? MaxDangerZoneOpacity : dangerZoneOpacity));
	CP_Graphics_DrawRect(x, y, w, h);
}

// 기본적으로 근접공격은 3초에서 1초 사이에 빨간색으로 공격 범위만큼 표시하고 공격한다.
// 그냥 정,직사각형을 
void EnemyCloseAttack1() // 한방향
{
	// 플레이어 위치를 기준으로 방향을 결정해서 공격함
	// x를 먼저 windowWidth / 2를 기준으로 큰지 작은지 나누고 그다음 y순
	if (currentEnemyFrame2 <= FRAME) {
		if (player.coord.x >= WindowWidthHalf)
		{
			if (player.coord.y >= WindowHeightHalf)  EnemyCloseAttackNum = 1; // 우하
			else EnemyCloseAttackNum = 2; // 우상
		}
		else {
			if (player.coord.y >= WindowHeightHalf) EnemyCloseAttackNum = 3; // 좌하
			else EnemyCloseAttackNum = 4; // 좌상
		}
	}
	
	switch (EnemyCloseAttackNum)
	{
		case 1 :
			if (!isCloseAttackCool)
				SignDanagerZone(WindowWidthHalf, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
		case 2 :
			if (!isCloseAttackCool)
				SignDanagerZone(WindowWidthHalf, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
		case 3 :
			if (!isCloseAttackCool)
				SignDanagerZone(enemy.range.x - enemy.recognizeRange, WindowHeightHalf, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
		case 4:
			if (!isCloseAttackCool)
				SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
			break;
	}
}
void EnemyCloseAttack2() // 수직 수평
{
	// x가 보스 크기 만큼의 좌표에 해당하는지 테스트하고 맞으면 수평, 아니면 수직으로 한다.
	if (currentEnemyFrame2 <= FRAME) {
		if (player.coord.x >= WindowWidthHalf - enemy.size / 2 && player.coord.x <= WindowWidthHalf + enemy.size) EnemyCloseAttackNum = 5;
		else EnemyCloseAttackNum = 6;
	}
	switch (EnemyCloseAttackNum)
	{
		case 5:	// 수평
			if (!isCloseAttackCool) {
				SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
				SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y + enemy.size, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
			}
			break;
		case 6: // 수직
			if (!isCloseAttackCool) {
				SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
				SignDanagerZone(enemy.range.x + enemy.size, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
			}
			break;
	}
}
void EnemyCloseAttack3() // 전방향
{
	// 전방향
	// 표시 n초간
	EnemyCloseAttackNum = 7;
	if (!isCloseAttackCool)
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.size + enemy.recognizeRange * 2);
	// 이후 공격
}

bool isPlayerIncludeRange()
{
	switch (EnemyCloseAttackNum)
	{
		CP_Vector rangeRect;
		float rangeSize = 0;
		float rectX = 0;
		float rectY = 0;
		case 1:
			rangeRect = enemy.coord;
			rectX = enemy.coord.x;
			rectY = enemy.size / 2 + enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			if (player.coord.x < WindowWidthHalf && player.coord.y < WindowHeightHalf)
				return 1;
		case 2:
			rangeRect.x = enemy.coord.x;
			rangeRect.y = enemy.range.y - enemy.recognizeRange;
			rectX = enemy.size / 2 + enemy.recognizeRange;
			rectY = enemy.size / 2 + enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			if (player.coord.x >= WindowWidthHalf && player.coord.y < WindowHeightHalf)
				return 1;
			break;
		case 3:
			rangeRect.x = enemy.range.x - enemy.recognizeRange;
			rangeRect.y = enemy.coord.y;
			rectX = enemy.size / 2 + enemy.recognizeRange;
			rectY = enemy.size / 2 + enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			if (player.coord.x < WindowWidthHalf && player.coord.y >= WindowHeightHalf)
				return 1;
			break;
		 case 4:
			rangeRect.x = enemy.range.x - enemy.recognizeRange;
			rangeRect.y = enemy.range.y - enemy.recognizeRange;
			rectX = enemy.size / 2 + enemy.recognizeRange;
			rectY = enemy.size / 2 + enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 5:
			rangeRect.x = enemy.range.x - enemy.recognizeRange;
			rangeRect.y = enemy.range.y - enemy.recognizeRange;
			rectX = enemy.size + enemy.recognizeRange * 2;
			rectY = enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			rangeRect.x = enemy.range.x - enemy.recognizeRange;
			rangeRect.y = enemy.range.y + enemy.size;
			rectX = enemy.size + enemy.recognizeRange * 2;
			rectY = enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 6:
			rangeRect.x = enemy.range.x - enemy.recognizeRange;
			rangeRect.y = enemy.range.y - enemy.recognizeRange;
			rectX = enemy.recognizeRange;
			rectY = enemy.size + enemy.recognizeRange * 2;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			rangeRect.x = enemy.range.x + enemy.size;
			rangeRect.y = enemy.range.y - enemy.recognizeRange;
			rectX = enemy.recognizeRange; 
			rectY = enemy.size + enemy.recognizeRange * 2;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 7:
			if (isPlayerInsideRange)
				return 1;
			break;
	}
	return 0;
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
