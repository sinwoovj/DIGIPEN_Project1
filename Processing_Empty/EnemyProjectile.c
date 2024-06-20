#include "EnemyProjectile.h"

void CreateEnemyProjectile(float x, float y, float velocity, int direction)
{
	for (int i = 0; i < MAX_ENEMYPROJECTIES; i++)
	{
		if (!enemyProjectile[i].active)
		{
			enemyProjectile[i].position_x = x;
			enemyProjectile[i].position_y = y;
			enemyProjectile[i].size = 10;
			enemyProjectile[i].velocity = velocity;
			enemyProjectile[i].active = 1;
			enemyProjectile[i].shape = Circle;
			enemyProjectile[i].direction = direction;
			break;
		}
	}
}

void DrawEnemyProjectile()
{
	for (int i = 0; i < MAX_ENEMYPROJECTIES; ++i) {
		if (enemyProjectile[i].active) {
			switch (enemyProjectile[i].direction)
			{
			case 0:
				enemyProjectile[i].position_x += enemyProjectile[i].velocity;
				break;
			case 1:
				enemyProjectile[i].position_x += enemyProjectile[i].velocity;
				enemyProjectile[i].position_y -= enemyProjectile[i].velocity;
				break;
			case 2:
				enemyProjectile[i].position_y -= enemyProjectile[i].velocity;
				break;
			case 3:
				enemyProjectile[i].position_x -= enemyProjectile[i].velocity;
				enemyProjectile[i].position_y -= enemyProjectile[i].velocity;
				break;
			case 4:
				enemyProjectile[i].position_x -= enemyProjectile[i].velocity;
				break;
			case 5:
				enemyProjectile[i].position_x -= enemyProjectile[i].velocity;
				enemyProjectile[i].position_y += enemyProjectile[i].velocity;
				break;
			case 6:
				enemyProjectile[i].position_y += enemyProjectile[i].velocity;
				break;
			case 7:
				enemyProjectile[i].position_x += enemyProjectile[i].velocity;
				enemyProjectile[i].position_y += enemyProjectile[i].velocity;
			}
			// 화면밖에 나가는 지 체크
			if (enemyProjectile[i].position_y < 0
				|| enemyProjectile[i].position_y > CP_System_GetWindowHeight()
				|| enemyProjectile[i].position_x < 0
				|| enemyProjectile[i].position_x > CP_System_GetWindowWidth())
			{
				enemyProjectile[i].active = 0;
			}
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Settings_EllipseMode(CP_POSITION_CENTER);
			CP_Graphics_DrawCircle(enemyProjectile[i].position_x, enemyProjectile[i].position_y, enemyProjectile[i].size);
		}
	}
}
