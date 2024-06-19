#include "Calculate.h"

bool RangeTest(CP_Vector v1, float v1_size, Shape v1_shape, CP_Vector v2, float v2_size, Shape v2_shape, float w, float h) { // v1¿Ã base, v2∞° target
	bool res = false;

	if (v1_shape == Square && v2_shape == Square)
	{
		CP_Vector coord[4];

		coord[0] = v2;

		coord[1].x = v2.x + v2_size;
		coord[1].y = v2.y;

		coord[2].x = v2.x;
		coord[2].y = v2.y + v2_size;

		coord[3].x = v2.x + v2_size;
		coord[3].y = v2.y + v2_size;

		for (int i = 0; i < 4; i++) {
			if (coord[i].x >= v1.x && coord[i].x <= v1.x + v1_size &&
				coord[i].y >= v1.y && coord[i].y <= v1.y + v1_size)
				res = true;
		}
	}
	else if (v1_shape == Square && v2_shape == Circle)
	{
		float x = abs(v1.x - v2.x) <= abs((v1.x + v1_size) - v2.x) ? v1.x : v1.x + v1_size;
		float y = abs(v1.y - v2.y) <= abs((v1.y + v1_size) - v2.y) ? v1.y : v1.y + v1_size;
		if (x <= v2_size / 2 && y <= v2_size / 2)
			res = true;
	}
	else if (v1_shape == Circle && v2_shape == Rect)
	{
		float x = abs(v1.x - v2.x) <= abs(v1.x - (v2.x + w)) ? v2.x : v2.x + w;
		float y = abs(v1.y - v2.y) <= abs(v1.y - (v2.y + h)) ? v2.y : v2.y + h;
		float diffX = v1.x >= x ? v1.x - x : x - v1.x;
		float diffy = v1.y >= y ? v1.y - y : y - v1.y;
		float diffF = sqrtf((diffX * diffX) + (diffy * diffy));
		if (v1_size /2 >= diffF)
			res = true;
	}
	else if (v1_shape == Circle && v2_shape == Circle)
	{
		float diffX = v1.x >= v2.x ? v1.x - v2.x : v2.x - v1.x;
		float diffy = v1.y >= v2.y ? v1.y - v2.y : v2.y - v1.y;
		float diffF = sqrtf((diffX * diffX) + (diffy * diffy));
		if ((v1_size / 2) + (v2_size / 2) >= diffF)
			res = true;
	}

	return res;
}