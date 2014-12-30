#include "scene.h"
#include "game.h"
#include "levelSelect.h"
#include "mainMenu.h"
#include "pauseMenu.h"
#include "resources.h"

using namespace IwTween;

#define FRAME_TIME  (30.0f / 1000.0f)

CTweenManager*  g_pTweener = 0;

int main() 
{
	Iw2DInit();

	while (!s3eDeviceCheckQuitRequest())
	{
		Iw2DSurfaceClear(0xff000000);
		Iw2DSurfaceShow();

		s3eDeviceYield();
	}

	Iw2DTerminate();

	return 0;
}
