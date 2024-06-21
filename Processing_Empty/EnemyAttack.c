#include "EnemyAttack.h"
#include "Player.h"
#include "cprocessing.h"
#include "Enemy.h"
#include "Standard.h"
#include "Calculate.h"
#include "Roughly.h"
#include <math.h>

void SignDanagerZone(float x, float y, float w, float h)
{
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, dangerZoneOpacity >= MaxDangerZoneOpacity ? MaxDangerZoneOpacity : dangerZoneOpacity));
	CP_Graphics_DrawRect(x, y, w, h);
}

void SignDanagerPatternZone(float x, float y, float w, float h)
{
	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, dangerZonePatternOpacity >= MaxDangerZoneOpacity ? MaxDangerZoneOpacity : dangerZonePatternOpacity));
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
			if (player.coord.y >= WindowHeightHalf)  EnemyCloseAttackNum = 1; // ����
			else EnemyCloseAttackNum = 2; // ���
		}
		else {
			if (player.coord.y >= WindowHeightHalf) EnemyCloseAttackNum = 3; // ����
			else EnemyCloseAttackNum = 4; // �»�
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
void EnemyCloseAttack2() // ���� ����
{
	// x�� ���� ũ�� ��ŭ�� ��ǥ�� �ش��ϴ��� �׽�Ʈ�ϰ� ������ ����, �ƴϸ� �������� �Ѵ�.
	if (currentEnemyFrame2 <= FRAME) {
		if (player.coord.x >= WindowWidthHalf - enemy.size / 2 && player.coord.x <= WindowWidthHalf + enemy.size) EnemyCloseAttackNum = 5;
		else EnemyCloseAttackNum = 6;
	}

	if (!isCloseAttackCool)
	{
		switch (EnemyCloseAttackNum)
		{
		case 5:	// ����
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y + enemy.size, enemy.size + enemy.recognizeRange * 2, enemy.recognizeRange);

			break;
		case 6: // ����
			SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);
			SignDanagerZone(enemy.range.x + enemy.size, enemy.range.y - enemy.recognizeRange, enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2);

			break;
		}
	}
}
void EnemyCloseAttack3() // ������
{
	// ������
	// ǥ�� n�ʰ�
	EnemyCloseAttackNum = 7;
	if (!isCloseAttackCool)
		SignDanagerZone(enemy.range.x - enemy.recognizeRange, enemy.range.y - enemy.recognizeRange, enemy.size + enemy.recognizeRange * 2, enemy.size + enemy.recognizeRange * 2);
	// ���� ����
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

// 1 : ����, 2 : ���, 3 : ����, 4 : �»�
void EnemyPatternAttack1()
{
	if (currentEnemyFrame3 <= FRAME * 2) {

		if (player.coord.x >= WindowWidthHalf)
		{
			if (player.coord.y >= WindowHeightHalf)  EnemyPatternAttackNum = 1; // ����
			else EnemyPatternAttackNum = 2; // ���
		}
		else {
			if (player.coord.y >= WindowHeightHalf) EnemyPatternAttackNum = 3; // ����
			else EnemyPatternAttackNum = 4; // �»�
		}
	}

	if (!isCloseAttackCool)
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
// 5 : ��, 6 : �� 7 : ��, 8 : ��
void EnemyPatternAttack2()
{
	// ���� ������ �� �߿��� �������� ���� �÷��̾� ��ġ�� �������� ä���Ѵ�.
	if (currentEnemyFrame3 <= FRAME * 2)
	{
		switch (enemy.patternRandomNum)
		{
			case 1: // ����
				if (player.coord.x >= WindowWidthHalf) EnemyPatternAttackNum = 5;
				else EnemyPatternAttackNum = 6;
				break;
			case 2: // ����
				if (player.coord.y >= WindowHeightHalf) EnemyPatternAttackNum = 7;
				else EnemyPatternAttackNum = 8;
				break;
		}
	}
	if (!isCloseAttackCool)
	{
		switch (EnemyPatternAttackNum)
		{
		case 5:	// ��
			SignDanagerPatternZone(WindowWidthHalf, 0, WindowWidthSize, WindowHeightSize);
			break;
		case 6: // ��
			SignDanagerPatternZone(0, 0, WindowWidthHalf, WindowHeightSize);
			break;
		case 7: // ��
			SignDanagerPatternZone(0, WindowHeightHalf, WindowWidthSize, WindowHeightSize);
			break;
		case 8: // ��
			SignDanagerPatternZone(0,0,WindowWidthSize,WindowHeightHalf);
			break;
		}
	}
}
// 9 : üũ1, 10 : üũ2
void EnemyPatternAttack3()
{
	float checkPatternWidthHeight = 120;
	// �� ���� ũ�� 120, ������ 16 : 9
	switch (enemy.patternRandomNum)
	{
		case 1:
			EnemyPatternAttackNum = 9;
			break;
		case 2:
			EnemyPatternAttackNum = 10;
			break;
	}

	if (!isCloseAttackCool)
	{
		switch (EnemyPatternAttackNum)
		{
			case 9: // ���� �� Ÿ��
				for (int i = 1; i <= 16; i++) {
					for (int j = 1; j <= 9; j++) {
						if (j % 2 == 0)
							SignDanagerPatternZone(0, j * checkPatternWidthHeight, WindowWidthSize, checkPatternWidthHeight);
					}
					if(i % 2 == 0)
						SignDanagerPatternZone(i * checkPatternWidthHeight, 0, checkPatternWidthHeight, WindowHeightSize);
				}
				break;
			case 10: // ���� �� ��Ÿ��
				for (int i = 1; i <= 16; i++) {
					for (int j = 1; j <= 9; j++) {
						if (j % 2 == 0)
							SignDanagerPatternZone(0, j * checkPatternWidthHeight, WindowWidthSize, checkPatternWidthHeight);
					}
					if (i % 2 == 0)
						SignDanagerPatternZone(i * checkPatternWidthHeight, 0, checkPatternWidthHeight, WindowHeightSize);
				}
				break;
		}
	}
}
// 11 : �����̵� ��>��, 12 : �����̵� ��>��, 13 : �����̵� ��>��, 14 : �����̵� ��>��
void EnemyPatternAttack4()
{
	//EnemyPatternAttackNum = 4;
}
// 15 : �����̵� üũ ����>�»�, 16 : �����̵� üũ ���>����, 17 : �����̵� ����>���, 18 : �����̵� �»�>����
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
	}
	return 0;
}
