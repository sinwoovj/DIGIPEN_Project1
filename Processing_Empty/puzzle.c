#include "puzzle.h"
void Draw()
{
	for (int i = 0; i < 2; i++)
	{
		CP_Graphics_DrawRect(Rect[i].x, Rect[i].y, Rect[i].size, Rect[i].size);
		CP_Settings_Fill(Rect[i].color);
	}
}

void Key()
{
	aoc = 10;
	if (CP_Input_KeyDown(KEY_W))
	{

		velocity += 0.5f;
		
		cnt--;
	}
	else if (CP_Input_KeyDown(KEY_S))
	{
		Rect[0].y += aoc;
		cnt--;
	}
	else if (CP_Input_KeyDown(KEY_D))
	{
		Rect[0].x += aoc;
		cnt--;
	}
	else if (CP_Input_KeyDown(KEY_A))
	{
		Rect[0].x -= aoc;
		cnt--;
	}
}
void CountText()
{
	char text[30];
	float textSize = 30.f;
	CP_Settings_TextSize(textSize);
	CP_Color fontcolor = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(fontcolor);
	sprintf_s(text, 30, "Movement: %i", cnt);
	CP_Font_DrawText(text, 30, 30);
}
void CollisionBox()
{

}

