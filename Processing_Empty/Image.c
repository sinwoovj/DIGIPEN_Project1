#include "Image.h"

void ImageLoad()
{
	BG = CP_Image_Load("./Assets/BG.png");

	BossFace = CP_Image_Load("./Assets/Boss.png");
	BossFace_Phase3 = CP_Image_Load("./Assets/Boss_Phase3.png");
	BossBlackFace = CP_Image_Load("./Assets/BossBlack.png");

	PlayerDir[0] = CP_Image_Load("./Assets/Front.png");
	PlayerDir[1] = CP_Image_Load("./Assets/Right.png");
	PlayerDir[2] = CP_Image_Load("./Assets/Back.png");
	PlayerDir[3] = CP_Image_Load("./Assets/Left.png");


	SwordImg[0] = CP_Image_Load("./Assets/Sword_0.png");
	SwordImg[1] = CP_Image_Load("./Assets/Sword_1.png");
	SwordImg[2] = CP_Image_Load("./Assets/Sword_2.png");
	SwordImg[3] = CP_Image_Load("./Assets/Sword_3.png");
	SwordImg[4] = CP_Image_Load("./Assets/Sword_4.png");
	SwordImg[5] = CP_Image_Load("./Assets/Sword_5.png");

	ArrowImg[0] = CP_Image_Load("./Assets/Arrow_1.png");
	ArrowImg[1] = CP_Image_Load("./Assets/Arrow_2.png");

	ThunderImg[0] = CP_Image_Load("./Assets/Thunder_0.png");
	ThunderImg[1] = CP_Image_Load("./Assets/Thunder_1.png");
	ThunderImg[2] = CP_Image_Load("./Assets/Thunder_2.png");
	ThunderImg[3] = CP_Image_Load("./Assets/Thunder_3.png");
	
	SpitImg = CP_Image_Load("./Assets/Spit.png");
	SpitImg_2 = CP_Image_Load("./Assets/Spit_2.png");

	Punch[0] = CP_Image_Load("./Assets/Punch_1.png");
	Punch[1] = CP_Image_Load("./Assets/Punch_2.png");
	Punch[2] = CP_Image_Load("./Assets/Punch_3.png");
	Punch[3] = CP_Image_Load("./Assets/Punch_4.png");

}

void ImageFree()
{
	CP_Image_Free(&BG);

	CP_Image_Free(&BossFace);
	CP_Image_Free(&BossBlackFace);
	CP_Image_Free(&SpitImg);
	CP_Image_Free(&SpitImg_2);

	for(int i = 0; i < 4; i++)
	{
		CP_Image_Free(&PlayerDir[i]);
		CP_Image_Free(&ThunderImg[i]);
		CP_Image_Free(&Punch[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		CP_Image_Free(&ArrowImg[i]);
	}
}
