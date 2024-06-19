#pragma once

#include "cprocessing.h"

CP_Image BG;

CP_Image BossFace;
CP_Image BossBlackFace;

CP_Image PlayerDir[4]; 

CP_Image SwordImg;
CP_Image ArrowImg;
CP_Image ElectroImg;

CP_Image SpitImg;

void ImageLoad();
void ImageFree();