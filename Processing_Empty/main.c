#include "cprocessing.h"
#include "Roughly.h"

int main(void)
{
	CP_Engine_SetNextGameState(Roughly_game_init, Roughly_game_update, Roughly_game_exit);
	CP_Engine_Run();
	return 0;
}
