#include "Intro.h"

#include "Standard.h"
#include "cprocessing.h"
#include "Roughly.h"
#include <stdbool.h>

int introInterval = FRAME * 2;
int introFrame = 0;
int introState = 0;



void goMain(void)
{
	CP_Engine_SetNextGameState(Roughly_game_init, Roughly_game_update, Roughly_game_exit);
}

bool introFrameCheck()
{
	if (++introFrame > introInterval)
	{
		introFrame = 0;
		return true;
	}
	return false;
}

CP_Image Digipen_logo;
CP_Image Team_logo;

void intro_init()
{
	Digipen_logo = CP_Image_Load("./Assets/DigiPen_WHITE.png");
	Team_logo = CP_Image_Load("./Assets/Team_Logo.png");
	StandardInit();
	CP_System_SetWindowSize(WindowWidthSize, WindowHeightSize);
}

void intro_update()
{

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	if (introFrameCheck())
	{
		introState++;
	}
	switch (introState)
	{
		case 0: // appear
			CP_Image_Draw(Digipen_logo, WindowWidthHalf, WindowHeightHalf, 1026, 248, (int)(((introFrame / 2) * 255) / introInterval));
			break;
		case 1: // static
			CP_Image_Draw(Digipen_logo, WindowWidthHalf, WindowHeightHalf, 1026, 248, 255);
			break;
		case 2: // disappear
			CP_Image_Draw(Digipen_logo, WindowWidthHalf, WindowHeightHalf, 1026, 248, 255 - (int)(((introFrame / 2) * 255) / introInterval));
			break;
		case 3: // appear
			CP_Image_Draw(Team_logo, WindowWidthHalf, WindowHeightHalf, 1026, 248, (int)(((introFrame / 2) * 255) / introInterval));
			break;
		case 4: // static
			CP_Image_Draw(Team_logo, WindowWidthHalf, WindowHeightHalf, 1026, 248,255);
			break;
		case 5: // disappear
			CP_Image_Draw(Team_logo, WindowWidthHalf, WindowHeightHalf, 1026, 248,255 - (int)(((introFrame / 2) * 255) / introInterval));
			break;
		case 6: // goMain
			goMain();
			break;
	}
}

void intro_exit()
{
	CP_Image_Free(&Digipen_logo);
	CP_Image_Free(&Team_logo);
}