#include "Iw2D.h"

int main()
{
	Iw2DInit();

	CIw2DImage* image = Iw2DCreateImage("textures/character.png");

	while(!s3eDeviceCheckQuitRequest())
	{
		Iw2DSurfaceClear(0xff000000);

		Iw2DDrawImage(image, CIwFVec2::g_AxisY);

		Iw2DSurfaceShow();

		s3eDeviceYield(0);
	}

	delete image;
	Iw2DTerminate();

	return 0;
}