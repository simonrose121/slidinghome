#include "Iw2D.h"
#include "input.h"
#include "audio.h"

int main()
{
	Iw2DInit();

	g_pInput = new Input();
	g_pAudio = new Audio();

	CIw2DImage* image = Iw2DCreateImage("textures/character.png");
	CIwFVec2 image_position = CIwFVec2::g_Zero;

	//main game loop
	while(!s3eDeviceCheckQuitRequest())
	{
		g_pInput->Update();
		g_pAudio->Update();

		Iw2DSurfaceClear(0xff000000);

		Iw2DDrawImage(image, image_position);

		Iw2DSurfaceShow();

		if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			image_position.x = (float)g_pInput->m_X;
			image_position.y = (float)g_pInput->m_Y;

			g_pInput->Reset();

			g_pAudio->PlaySound("audio/gem_destroyed.wav");
		}

		s3eDeviceYield(0);
	}

	//clean up
	delete image;
	delete g_pInput;
	delete g_pAudio;
	Iw2DTerminate();

	return 0;
}