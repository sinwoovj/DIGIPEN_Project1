#include "EnemyProjectile.h"
#include "Player.h"
void CreateEnemyProjectile(float x, float y, float velocity, int direction)
{
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		if (!enemyProjectile[i].active)
		{
			enemyProjectile[i].position.x = x;
			enemyProjectile[i].position.y = y;
			enemyProjectile[i].size = 10;
			enemyProjectile[i].velocity = velocity;
			enemyProjectile[i].active = 1;
			enemyProjectile[i].shape = Circle;
			enemyProjectile[i].direction = direction;
			break;
		}
	}
}

void CreateEnemyProjectile_2(float x, float y, float velocity, int direction)
{
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		if (!enemyProjectile_2[i].active)
		{
			enemyProjectile_2[i].position.x = x;
			enemyProjectile_2[i].position.y = y;
			enemyProjectile_2[i].size = 10;
			enemyProjectile_2[i].velocity = velocity;
			enemyProjectile_2[i].active = 1;
			enemyProjectile_2[i].shape = Circle;
			enemyProjectile_2[i].direction = direction;

			enemyProjectile_2[i].target = player.coord;
			break;
		}
	}
}

void DrawEnemyProjectile() // 원형 수평 수직
{
	for (int i = 0; i < MAX_ENEMYPROJECTIES; ++i) {
		if (enemyProjectile[i].active) {
			switch (enemyProjectile[i].direction)
			{
			case 0:
				enemyProjectile[i].position.x += enemyProjectile[i].velocity;
				break;
			case 1:
				enemyProjectile[i].position.x += enemyProjectile[i].velocity;
				enemyProjectile[i].position.y -= enemyProjectile[i].velocity;
				break;
			case 2:
				enemyProjectile[i].position.y -= enemyProjectile[i].velocity;
				break;
			case 3:
				enemyProjectile[i].position.x -= enemyProjectile[i].velocity;
				enemyProjectile[i].position.y -= enemyProjectile[i].velocity;
				break;
			case 4:
				enemyProjectile[i].position.x -= enemyProjectile[i].velocity;
				break;
			case 5:
				enemyProjectile[i].position.x -= enemyProjectile[i].velocity;
				enemyProjectile[i].position.y += enemyProjectile[i].velocity;
				break;
			case 6:
				enemyProjectile[i].position.y += enemyProjectile[i].velocity;
				break;
			case 7:
				enemyProjectile[i].position.x += enemyProjectile[i].velocity;
				enemyProjectile[i].position.y += enemyProjectile[i].velocity;
			}
			// 화면밖에 나가는 지 체크
			if (enemyProjectile[i].position.y < 0
				|| enemyProjectile[i].position.y > CP_System_GetWindowHeight()
				|| enemyProjectile[i].position.x < 0
				|| enemyProjectile[i].position.x > CP_System_GetWindowWidth())
			{
				enemyProjectile[i].active = 0;
			}
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_EllipseMode(CP_POSITION_CENTER);
			CP_Graphics_DrawCircle(enemyProjectile[i].position.x, enemyProjectile[i].position.y, enemyProjectile[i].size);
		}
	}
}

CP_Vector CP_VectorSubtract(CP_Vector a, CP_Vector b)
{
	CP_Vector result = { a.x - b.x, a.y - b.y };
	return result;
}
CP_Vector CP_VectorNormalize(CP_Vector v)
{
	float length = sqrtf(v.x * v.x + v.y * v.y);
	CP_Vector result = { v.x / length, v.y / length };
	return result;
}
CP_Vector CP_VectorScale(CP_Vector v, float scale)
{
	CP_Vector result = { v.x * scale, v.y * scale };
	return result;
}
float CP_VectorDistance(CP_Vector a, CP_Vector b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrtf(dx * dx + dy * dy);
}

void DrawEnemyProjectile_2() // 유도
{
	for (int i = 0; i < MAX_ENEMYPROJECTIES; ++i) {
		if (enemyProjectile_2[i].active) {
			// 현재 탄환의 목표 방향 계산
			CP_Vector direction = CP_VectorSubtract(enemyProjectile_2[i].target, enemyProjectile_2[i].position);
			direction = CP_VectorNormalize(direction);
			direction = CP_VectorScale(direction, enemyProjectile_2[i].velocity * CP_System_GetDt());

			// 탄환의 위치 업데이트
			enemyProjectile_2[i].position.x += direction.x;
			enemyProjectile_2[i].position.y += direction.y;

			// 목표 지점에 도달했는지 체크
			float threshold = enemyProjectile_2[i].velocity * CP_System_GetDt(); // 속도에 비례한 임계값
			if (CP_VectorDistance(enemyProjectile_2[i].position, enemyProjectile_2[i].target) < threshold) // 1.0f는 임계값
			{
				enemyProjectile_2[i].position.x = 0;
				enemyProjectile_2[i].position.y = 0;
				enemyProjectile_2[i].active = 0;
			}

			// 화면밖에 나가는 지 체크
			if (enemyProjectile_2[i].position.y < 0
				|| enemyProjectile_2[i].position.y > CP_System_GetWindowHeight()
				|| enemyProjectile_2[i].position.x < 0
				|| enemyProjectile_2[i].position.x > CP_System_GetWindowWidth())
			{
				enemyProjectile_2[i].active = 0;
			}
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_EllipseMode(CP_POSITION_CENTER);
			CP_Graphics_DrawCircle(enemyProjectile_2[i].position.x, enemyProjectile_2[i].position.y, enemyProjectile_2[i].size);
		}
	}
}