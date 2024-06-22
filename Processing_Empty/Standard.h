#pragma once
#define FRAME 30

typedef enum Shape {
	Square,
	Rect,
	Circle
}Shape;

//Initialize WindowSize
float WindowWidthSize;
float WindowHeightSize;
float WindowWidthHalf; // windowWinth / 2
float WindowHeightHalf; // windowHeight / 2
void StandardInit();