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

void Create_Projectile(float x, float y, float velocity)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (!test[i].active)
		{
			test[i].projectile_position_x = x;
			test[i].projectile_position_y = y;
			test[i].projectile_size = 10;
			test[i].projectile_velocity = velocity;
			test[i].active = 1;
			break;
		}
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
		test[i].active = 0;
	}
}

void Roughly_game_update(void)
{
	//Initialize Setting
	CP_Color myColor = CP_Color_Create(0, 255, 255, 255);
	CP_Graphics_ClearBackground(myColor);

	Draw();
	Key();


	if (CP_Input_MouseClicked())
	{
		float velocity = 0.5f;
		Create_Projectile(Rect.x + 20, Rect.y + 20, velocity);
	}
	//클릭하고 나서 투사체가 바로 사라짐, 클릭하면 계속 맵에 남아있게 수정.

	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (test[i].active) {
			test[i].projectile_position_x += test[i].projectile_velocity;
			test[i].projectile_position_y += test[i].projectile_velocity;

			// 화면밖에 나가는 지 체크
			if (test[i].projectile_position_y < 0 || test[i].projectile_position_y > CP_System_GetWindowHeight() || test[i].projectile_position_x < 0 || test[i].projectile_position_x > CP_System_GetWindowWidth()) {
				test[i].active = 0;
			}


			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawCircle(test[i].projectile_position_x, test[i].projectile_position_y, test[i].projectile_size);
		}
	}


	//distance = velocity * CP_System_GetDt();
}

void Roughly_game_exit(void)
{

}