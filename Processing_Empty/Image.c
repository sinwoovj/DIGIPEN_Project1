#include "Image.h"

void ImageLoad()
{
	BG = CP_Image_Load("./Assets/BG.png");

	BossFace = CP_Image_Load("./Assets/Boss.png");
	BossBlackFace = CP_Image_Load("./Assets/BossBlack.png");

	PlayerDir[0] = CP_Image_Load("./Assets/Front.png");
	PlayerDir[1] = CP_Image_Load("./Assets/Right.png");
	PlayerDir[2] = CP_Image_Load("./Assets/Back.png");
	PlayerDir[3] = CP_Image_Load("./Assets/Left.png");
}

void ImageFree()
{
	CP_Image_Free(&BG);

	CP_Image_Free(&BossFace);
	CP_Image_Free(&BossBlackFace);

	for(int i = 0; i < 4; i++)
		CP_Image_Free(&PlayerDir[i]);
}
