#pragma once

#include <stdbool.h>
#include "cprocessing.h"
#include "Standard.h"

bool isWithinBoundary(float v1_x, float v1_y, float v2_x, float v2_y, float w, float h);
bool RangeTest(CP_Vector v1, float v1_size, Shape v1_shape, CP_Vector v2, float v2_size, Shape v2_shape, float w, float h);