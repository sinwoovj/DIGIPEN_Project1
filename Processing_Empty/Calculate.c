#include "Calculate.h"

bool RangeTest(CP_Vector v1, float v1_size, Shape v1_shape, CP_Vector v2, float v2_size, Shape v2_shape) { // v1�� base, v2�� target
	bool res = false;

	if (v1_shape == Rect && v2_shape == Rect)
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
	else if (v1_shape == Rect && v2_shape == Circle)
	{
		float x = abs(v1.x - v2.x) <= abs((v1.x + v1_size) - v2.x) ? v1.x : v1.x + v1_size;
		float y = abs(v1.y - v2.y) <= abs((v1.y + v1_size) - v2.y) ? v1.y : v1.y + v1_size;
		if (x <= v2_size && y <= v2_size)
			res = true;
	}
	else if (v1_shape == Circle && v2_shape == Rect)
	{
		float x = abs(v2.x - v1.x) <= abs((v2.x + v2_size) - v1.x) ? v2.x : v2.x + v2_size;
		float y = abs(v2.y - v1.y) <= abs((v2.y + v2_size) - v1.y) ? v2.y : v2.y + v2_size;
		if (x <= v1_size && y <= v1_size)
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