#include "Projectile.h"

void Create_Projectile(float x, float y, float velocity)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (!projectile[i].active)
		{
			projectile[i].position_x = x;
			projectile[i].position_y = y;
			projectile[i].size = 10;
			projectile[i].velocity = velocity;
			projectile[i].active = 1;
			break;
		}
	}

}

void Draw_RightProjectile()
{
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (projectile[i].active) {
			projectile[i].position_x += projectile[i].velocity;

			// 화면밖에 나가는 지 체크
			if (projectile[i].position_x < 0 || projectile[i].position_x > CP_System_GetWindowWidth()) {
				projectile[i].active = 0;
			}

			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawCircle(projectile[i].position_x, projectile[i].position_y, projectile[i].size);
		}
	}
}

void Draw_Projectile()
{
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (projectile[i].active) {
			projectile[i].position_x += projectile[i].velocity;
			projectile[i].position_y += projectile[i].velocity;

			// 화면밖에 나가는 지 체크
			if (projectile[i].position_y < 0 || projectile[i].position_y > CP_System_GetWindowHeight() || projectile[i].position_x < 0 || projectile[i].position_x > CP_System_GetWindowWidth()) {
				projectile[i].active = 0;
			}


			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawCircle(projectile[i].position_x, projectile[i].position_y, projectile[i].size);
		}
	}
}