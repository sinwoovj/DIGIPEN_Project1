//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright ?2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include "puzzle.h"
void game_exit(void);

void game_init(void)
{
	Rect[0].x = 100.f, Rect[0].y = 100.f, Rect[0].size = 50.f, Rect[0].color = CP_Color_Create(0, 0, 255, 255);
	Rect[1].x = 250.f, Rect[1].y = 100.f, Rect[1].size = 50.f, Rect[1].color = CP_Color_Create(0, 255, 0, 255);
	cnt = 10;
	velocity = 0.05f;
}

void game_update(void)
{
	//Initialize Setting
	CP_Color myColor = CP_Color_Create(0, 255, 255, 255);
	CP_Graphics_ClearBackground(myColor);

	Draw();
	if(CP_Input_KeyDown(KEY_ANY))
		Key();
	
	CountText();
	distance = velocity * CP_System_GetDt();
	Rect[0].y -= distance;
	/*if (cnt == 0)
	{
		CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);

	}*/
}

void game_exit(void)
{

}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
