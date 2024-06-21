#pragma once

#define FRAME 30

float WindowWidthSize;
float WindowHeightSize;
float WindowWidthHalf; // windowWinth / 2
float WindowHeightHalf; // windowHeight / 2

typedef enum Shape {
	Square,
	Rect,
	Circle
}Shape;

void StandardInit();