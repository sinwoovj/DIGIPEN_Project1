#include "Roughly.h"
const int WindowWidth = 1920;
const int WindowHeight = 1080;

//Initialize Setting
void Init()
{
	//Player size setting
	player.coord.x = 100.f, player.coord.y = 100.f, player.size = 50.f;
	
	aoc = 10; //Move distance

	//Active Projectile
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projectile[i].active = 0;
	}

	CP_System_SetWindowSize(WindowWidth, WindowHeight);
}


void Roughly_game_init(void)
{
	Init(); //Initialize
}

void Roughly_game_update(void)
{
	CP_Color myColor = CP_Color_Create(0, 255, 255, 255);//Draw Background
	CP_Graphics_ClearBackground(myColor);
	CP_Graphics_DrawRect(player.coord.x, player.coord.y, player.size, player.size); //Draw Player

	PlayerMove();
	PlayerAttack();

	Draw_Projectile();



	//distance = velocity * CP_System_GetDt();
}

void Roughly_game_exit(void)
{

}