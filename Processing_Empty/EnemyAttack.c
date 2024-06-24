#include "EnemyAttack.h"
#include "Player.h"
#include "cprocessing.h"
#include "Enemy.h"
#include "Standard.h"
#include "Calculate.h"
#include "Roughly.h"
#include "EnemyProjectile.h"
#include "Image.h"
#include <math.h>

float checkPatternWidthHeight = 120;

int punchFrame = 0;

void SignDanagerZone(float x, float y, float w, float h)
{
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, dangerZoneOpacity >= MaxDangerZoneOpacity ? MaxDangerZoneOpacity : dangerZoneOpacity));
	CP_Graphics_DrawRect(x, y, w, h);

	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
}


void SignCheckPatternZone(float x, float y, float w, float h, int num, int punchFrmae)
{
	CP_Image_Draw(Punch[punchFrame], x + (w / 2.f), y + h - (h / 4.f), 90, 190, 255);
}

void SignDanagerPatternZone(float x, float y, float w, float h)
{
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, dangerZonePatternOpacity >= MaxDangerZoneOpacity ? MaxDangerZoneOpacity : dangerZonePatternOpacity));
	CP_Graphics_DrawRect(x, y, w, h);
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
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

	if (!isCloseAttackCool)
	{
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
			case 4:
					SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange, enemy.size / 2 + enemy.recognizeRange);
				break;
		}
	}
}
void EnemyCloseAttack2() // 수직 수평
{
	// x가 보스 크기 만큼의 좌표에 해당하는지 테스트하고 맞으면 수평, 아니면 수직으로 한다.
	if (currentEnemyFrame2 <= FRAME) {
		if (player.coord.x >= WindowWidthHalf - enemy.size / 2 && player.coord.x <= WindowWidthHalf + enemy.size) EnemyCloseAttackNum = 5;
		else EnemyCloseAttackNum = 6;
	}

	if (!isCloseAttackCool)
	{
		switch (EnemyCloseAttackNum)
		{
		case 5:	// 수평
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y + enemy.size, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);

			break;
		case 6: // 수직
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
			SignDanagerZone(enemy.range.x + enemy.size, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);

			break;
		}
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
		float rectX = 0;
		float rectY = 0;
		case 1:
			rangeRect = enemy.coord;
			rectX = enemy.coord.x;
			rectY = enemy.size / 2 + enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
		case 2:
			rangeRect.x = enemy.coord.x;
			rangeRect.y = enemy.range.y - enemy.recognizeRange;
			rectX = enemy.size / 2 + enemy.recognizeRange;
			rectY = enemy.size / 2 + enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 3:
			rangeRect.x = enemy.range.x - enemy.recognizeRange;
			rangeRect.y = enemy.coord.y;
			rectX = enemy.size / 2 + enemy.recognizeRange;
			rectY = enemy.size / 2 + enemy.recognizeRange;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
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

void EnemyProjectileRandomAttack1() // 원형
{
	float degree = 0.f;
	float velocity = 10.0f;
	int direction = 0;
	for (int i = 0; i < 16 * enemy.phase; i++)
	{
		CreateEnemyProjectile(WindowWidthHalf + (enemy.size / 2.0f) * cosf(CP_Math_Radians(degree)), WindowHeightHalf + (enemy.size / 2.0f) * sinf(CP_Math_Radians(degree)), velocity, direction);
		direction++;
		if (direction == 8) direction = 0;
		degree -= 45;
		if (degree == -405) degree = 0;
	}
	/*degree -= 90;
	CreateEnemyProjectile(WindowWidthHalf + 50 * (float)cos(degree), WindowHeightHalf + 50 * (float)sin(degree), velocity, 2);*/
}
void EnemyProjectileRandomAttack2() // 수평 수직
{
	float degree = 0.f;
	float velocity = 10.0f;
	int direction = 0;
	for (int i = 0; i < 8 * enemy.phase; i++)
	{
		CreateEnemyProjectile(WindowWidthHalf + (enemy.size / 2.0f) * cosf(CP_Math_Radians(degree)), WindowHeightHalf + (enemy.size / 2.0f) * sinf(CP_Math_Radians(degree)), velocity, direction);
		direction += 2;
		if (direction == 8) direction = 0;
		degree -= 90;
		if (degree == -450) degree = 0;
	}
}
void EnemyProjectileRandomAttack3() // 유도
{
	float degree = 0.f;
	float velocity = 150.0f * enemy.phase ;
	int direction = 0;
	for (int i = 0; i < 4 * enemy.phase; i++)
	{
		CreateEnemyProjectile_2(WindowWidthHalf + (enemy.size / 2.0f) * cosf(CP_Math_Radians(degree)), WindowHeightHalf + (enemy.size / 2.0f) * sinf(CP_Math_Radians(degree)), velocity, direction);
		direction += 2;
		if (direction == 4) direction = 0;
		degree -= 90;
		if (degree == -450) degree = 0;
	}
}

// 1 : 우하, 2 : 우상, 3 : 좌하, 4 : 좌상
void EnemyPatternAttack1()
{
	if (currentEnemyFrame3 <= FRAME) {

		if (player.coord.x >= WindowWidthHalf)
		{
			if (player.coord.y >= WindowHeightHalf)  EnemyPatternAttackNum = 1; // 우하
			else EnemyPatternAttackNum = 2; // 우상
		}
		else {
			if (player.coord.y >= WindowHeightHalf) EnemyPatternAttackNum = 3; // 좌하
			else EnemyPatternAttackNum = 4; // 좌상
		}
	}

	if (!isPatternAttackCool)
	{
		switch (EnemyPatternAttackNum)
		{
		case 1:
			SignDanagerPatternZone(WindowWidthHalf, WindowHeightHalf, WindowWidthHalf, WindowHeightHalf);
			break;
		case 2:
			SignDanagerPatternZone(WindowWidthHalf, 0, WindowWidthHalf, WindowHeightHalf);
			break;
		case 3:
			SignDanagerPatternZone(0, WindowHeightHalf, WindowWidthHalf, WindowHeightHalf);
			break;
		case 4:
			SignDanagerPatternZone(0, 0, WindowWidthHalf, WindowHeightHalf);
			break;
		}
	}
}
// 5 : 우, 6 : 좌 7 : 하, 8 : 상
void EnemyPatternAttack2()
{
	// 수평 수직을 둘 중에서 랜덤으로 고르고 플레이어 위치를 기준으로 채택한다.
	if (currentEnemyFrame3 <= FRAME)
	{
		switch (enemy.patternRandomNum)
		{
		case 1: // 수직
			if (player.coord.x >= WindowWidthHalf) EnemyPatternAttackNum = 5;
			else EnemyPatternAttackNum = 6;
			break;
		case 2: // 수평
			if (player.coord.y >= WindowHeightHalf) EnemyPatternAttackNum = 7;
			else EnemyPatternAttackNum = 8;
			break;
		}
	}
	if (!isPatternAttackCool)
	{
		switch (EnemyPatternAttackNum)
		{
		case 5:	// 우
			SignDanagerPatternZone(WindowWidthHalf, 0, WindowWidthSize, WindowHeightSize);
			break;
		case 6: // 좌
			SignDanagerPatternZone(0, 0, WindowWidthHalf, WindowHeightSize);
			break;
		case 7: // 하
			SignDanagerPatternZone(0, WindowHeightHalf, WindowWidthSize, WindowHeightSize);
			break;
		case 8: // 상
			SignDanagerPatternZone(0, 0, WindowWidthSize, WindowHeightHalf);
			break;
		}
	}
}
// 9 : 체크1, 10 : 체크2
void EnemyPatternAttack3()
{
	// 한 블럭의 크기 120, 비율은 16 : 9
	switch (enemy.patternRandomNum)
	{
	case 1:
		EnemyPatternAttackNum = 9;
		break;
	case 2:
		EnemyPatternAttackNum = 10;
		break;
	}

	if (!isPatternAttackCool)
	{
		switch (EnemyPatternAttackNum)
		{
		case 9: // 왼쪽 위 타격
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 9; j++) {

					if (i % 2 == 0)
					{
						if (j % 2 == 1) {
							SignDanagerPatternZone(i * checkPatternWidthHeight, j * checkPatternWidthHeight,
								checkPatternWidthHeight, checkPatternWidthHeight);
						}
					}
					else
					{
						if (j % 2 == 0) {
							SignDanagerPatternZone(i * checkPatternWidthHeight, j * checkPatternWidthHeight,
								checkPatternWidthHeight, checkPatternWidthHeight);
						}
					}
				}
			}
			break;
		case 10: // 왼쪽 위 비타격
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 9; j++) {

					if (i % 2 == 1)
					{
						if (j % 2 == 1) {
							SignDanagerPatternZone(i * checkPatternWidthHeight, j * checkPatternWidthHeight,
								checkPatternWidthHeight, checkPatternWidthHeight);
						}
					}
					else
					{
						if (j % 2 == 0) {
							SignDanagerPatternZone(i * checkPatternWidthHeight, j * checkPatternWidthHeight,
								checkPatternWidthHeight, checkPatternWidthHeight);
						}
					}
				}
			}
			break;
		}
	}
}
// 11 : 슬라이드 우>좌, 12 : 슬라이드 좌>우, 13 : 슬라이드 하>상, 14 : 슬라이드 상>하
void EnemyPatternAttack4()
{
	//EnemyPatternAttackNum = 4;
}
// 15 : 슬라이드 체크 우하>좌상, 16 : 슬라이드 체크 우상>좌하, 17 : 슬라이드 좌하>우상, 18 : 슬라이드 좌상>우하
void EnemyPatternAttack5 ()
{
	//EnemyPatternAttackNum = 5;
}
bool isPlayerIncludePatternRange()
{
	CP_Vector rangeRect;
	float rectX = 0;
	float rectY = 0;
	switch (EnemyPatternAttackNum)
	{
		case 1: // 우하
			rangeRect = enemy.coord;
			rectX = WindowWidthHalf;
			rectY = WindowHeightHalf;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
		case 2: // 우상
			rangeRect.x = enemy.coord.x;
			rangeRect.y = 0;
			rectX = WindowWidthHalf;
			rectY = WindowHeightHalf;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 3: // 좌하
			rangeRect.x = 0;
			rangeRect.y = enemy.coord.y;
			rectX = WindowWidthHalf;
			rectY = WindowHeightHalf;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
		case 4: // 좌상
			rangeRect.x = 0;
			rangeRect.y = 0;
			rectX = WindowWidthHalf;
			rectY = WindowHeightHalf;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 5: // 우
			rangeRect.x = enemy.coord.x;
			rangeRect.y = 0;
			rectX = WindowWidthHalf;
			rectY = WindowHeightSize;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 6: // 좌
			rangeRect.x = 0;
			rangeRect.y = 0;
			rectX = WindowWidthHalf;
			rectY = WindowHeightSize;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 7: // 하
			rangeRect.x = 0;
			rangeRect.y = enemy.coord.y;
			rectX = WindowWidthSize;
			rectY = WindowHeightHalf;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 8: // 상
			rangeRect.x = 0;
			rangeRect.y = 0;
			rectX = WindowWidthSize;
			rectY = WindowHeightHalf;
			if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
				return 1;
			break;
		case 9: // 체크 1 (왼쪽 위 O)
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 9; j++) {
					if (i % 2 == 0)
					{
						if (j % 2 == 1) {
							rangeRect.x = i * checkPatternWidthHeight;
							rangeRect.y = j * checkPatternWidthHeight;
							rectX = checkPatternWidthHeight;
							rectY = checkPatternWidthHeight;
							if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
								return 1;
						}
					}
					else
					{
						if (j % 2 == 0) {
							rangeRect.x = i * checkPatternWidthHeight;
							rangeRect.y = j * checkPatternWidthHeight;
							rectX = checkPatternWidthHeight;
							rectY = checkPatternWidthHeight;
							if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
								return 1;
						}
					}
				}
			}
			break;
		case 10: // 체크 2 (왼쪽 위 X)
			for (int i = 0; i < 16; i++) {
				for (int j = 0; j < 9; j++) {
					if (i % 2 == 1)
					{
						if (j % 2 == 1) {
							rangeRect.x = i * checkPatternWidthHeight;
							rangeRect.y = j * checkPatternWidthHeight;
							rectX = checkPatternWidthHeight;
							rectY = checkPatternWidthHeight;
							if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
								return 1;
						}
					}
					else
					{
						if (j % 2 == 0) {
							rangeRect.x = i * checkPatternWidthHeight;
							rangeRect.y = j * checkPatternWidthHeight;
							rectX = checkPatternWidthHeight;
							rectY = checkPatternWidthHeight;
							if (RangeTest(player.coord, player.size, player.shape, rangeRect, 0, Rect, rectX, rectY))
								return 1;
						}
					}
				}
			}
			break;
	}
	return 0;
}
