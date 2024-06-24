#pragma once
#include "cprocessing.h"
#include "PlayerProjectile.h"
#include "PlayerAttack.h"
#include "Image.h"

void Create_PlayerProjectile(float x, float y, float velocity, int direction)
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
			projectile[i].shape = Circle;
			projectile[i].direction = direction;
			break;
		}
	}
}

int arrowFrame = 0;
int swap = 0;
void Draw_PlayerProjectile()
{
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (projectile[i].active) {
			arrowFrame++;
			if (arrowFrame >= 5) // Change 10 to control animation speed
			{
				swap = !swap;
				arrowFrame = 0;
			}
			switch (projectile[i].direction)
			{
				case 1:
					projectile[i].position_x += projectile[i].velocity;
					CP_Image_DrawAdvanced(ArrowImg[swap], projectile[i].position_x - 10, projectile[i].position_y, 50, 15, 255, 0);
					break;
				case 2:
					projectile[i].position_x -= projectile[i].velocity;
					CP_Image_DrawAdvanced(ArrowImg[swap], projectile[i].position_x - 10, projectile[i].position_y, 50, 15, 255, 180);
					break;
				case 3:
					projectile[i].position_y -= projectile[i].velocity;
					CP_Image_DrawAdvanced(ArrowImg[swap], projectile[i].position_x - 10, projectile[i].position_y, 50, 15, 255, -90);
					break;
				case 4:
					projectile[i].position_y += projectile[i].velocity;
					CP_Image_DrawAdvanced(ArrowImg[swap], projectile[i].position_x - 10, projectile[i].position_y, 50, 15, 255, 90);
					break;
			}
			// 화면밖에 나가는 지 체크
			if (projectile[i].position_y < 0 
				|| projectile[i].position_y > CP_System_GetWindowHeight() 
				|| projectile[i].position_x < 0 
				|| projectile[i].position_x > CP_System_GetWindowWidth()) 
			{
				projectile[i].active = 0;
			}
		}
	}
}
