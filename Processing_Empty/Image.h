#pragma once

#include "cprocessing.h"
#define thunderFrameNum 4
#define swordFrameNum 6
#define punchFrameNum 4

CP_Image BG;

CP_Image BossFace;
CP_Image BossFace_Phase3;
CP_Image BossBlackFace;

CP_Image PlayerDir[4];


CP_Image SwordImg[swordFrameNum];
CP_Image ArrowImg[2];
CP_Image ThunderImg[thunderFrameNum];

CP_Image SpitImg;
CP_Image SpitImg_2;

CP_Image Punch[punchFrameNum];


void ImageLoad();
void ImageFree();