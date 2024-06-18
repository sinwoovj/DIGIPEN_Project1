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
#include "Roughly.h"



int main(void)
{
	CP_Engine_SetNextGameState(Roughly_game_init, Roughly_game_update, Roughly_game_exit);
	CP_Engine_Run();
	return 0;
}
