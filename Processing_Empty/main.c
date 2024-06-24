#include "cprocessing.h"
#include "Intro.h"

int main(void)
{
	CP_Engine_SetNextGameState(intro_init, intro_update, intro_exit);
	CP_Engine_Run();
	return 0;
}
