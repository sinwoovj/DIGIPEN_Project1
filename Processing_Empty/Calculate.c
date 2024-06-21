#include "Calculate.h"
#include "math.h"

bool isWithinBoundary(float v1_x, float v1_y, float v2_x, float v2_y, float w, float h) {
	return (v1_x >= v2_x && v1_x <= v2_x + w) && (v1_y >= v2_y && v1_y <= v2_y + h);
}

bool RangeTest(CP_Vector v1, float v1_size, Shape v1_shape, CP_Vector v2, float v2_size, Shape v2_shape, float w, float h) { // v1�� base, v2�� target
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
		// �簢���� ���� ����� �� ã��
		float closestX = fmax(v1.x, fmin(v2.x, v1.x + v1_size));
		float closestY = fmax(v1.y, fmin(v2.y, v1.y + v1_size));

		// ���� ����� ���� ���� �߽� ������ �Ÿ� ���
		float distanceX = v2.x - closestX;
		float distanceY = v2.y - closestY;

		// ��Ŭ���� �Ÿ� ���
		float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

		// �Ÿ��� ���� ���������� �۰ų� ������ �浹
		if (distance <= v2_size / 2) {
			res = true;
		}
	}
	else if (v1_shape == Circle && v2_shape == Rect)
	{
		// ���� �ڵ� ����
		float x = abs(v1.x - v2.x) <= abs(v1.x - (v2.x + w)) ? v2.x : v2.x + w;
		float y = abs(v1.y - v2.y) <= abs(v1.y - (v2.y + h)) ? v2.y : v2.y + h;
		float diffX = v1.x >= x ? v1.x - x : x - v1.x;
		float diffy = v1.y >= y ? v1.y - y : y - v1.y;
		float diffF = sqrtf((diffX * diffX) + (diffy * diffy));

		// ���ο� ���� �߰�
		if (v1_size / 2 >= diffF || isWithinBoundary(v1.x, v1.y, v2.x, v2.y, w, h))
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