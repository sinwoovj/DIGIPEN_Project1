#include "Roughly.h"
void Draw()
{
	for (int i = 0; i < 2; i++)
	{
		CP_Graphics_DrawRect(Rect.x, Rect.y, Rect.size, Rect.size);
		CP_Settings_Fill(Rect.color);
	}
}

void Key()
{
	if (CP_Input_KeyDown(KEY_W))
	{
		//velocity += 0.5f;
		Rect.y -= aoc;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		Rect.y += aoc;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		Rect.x += aoc;
	}
	else if (CP_Input_KeyDown(KEY_A))
	{
		Rect.x -= aoc;
	}
}



//void CountText()
//{
//	char text[30];
//	float textSize = 30.f;
//	CP_Settings_TextSize(textSize);
//	CP_Color fontcolor = CP_Color_Create(0, 0, 0, 255);
//	CP_Settings_Fill(fontcolor);
//	sprintf_s(text, 30, "Movement: %i", cnt);
//	CP_Font_DrawText(text, 30, 30);
//}


void Roughly_game_init(void)
{

	Rect.x = 100.f, Rect.y = 100.f, Rect.size = 50.f, Rect.color = CP_Color_Create(0, 0, 255, 255);
	aoc = 10;

	//Active vs Deactive
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		projectile[i].active = 0;
	}
}

void Roughly_game_update(void)
{
	//Initialize Setting
	CP_Color myColor = CP_Color_Create(0, 255, 255, 255);
	CP_Graphics_ClearBackground(myColor);

	Draw();
	Key();

	/*if (CP_Input_MouseClicked())
	{
		float velocity = 0.5f;
		Create_Projectile(Rect.x + 20, Rect.y + 20, velocity);
	}*/

	if (CP_Input_KeyTriggered(KEY_RIGHT))
	{
		float velocity = 1.0f;
		Create_Projectile(Rect.x + 20, Rect.y + 20, velocity);
		if(!Right)
			Right = !Right;
	}
	if(Right)
		Draw_RightProjectile();

	//distance = velocity * CP_System_GetDt();
}

void Roughly_game_exit(void)
{

}