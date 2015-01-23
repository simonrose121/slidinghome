#include "Iw2D.h"
#include "IwTween.h"
#include "input.h"
#include "audio.h"
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

	g_pResources = new Resources();
	g_pTweener = new CTweenManager();
	g_pInput = new Input();
	g_pAudio = new Audio();
	g_pSceneManager = new SceneManager();

	Game* game = new Game();
	game->SetName("game");
	game->Init(11, 17);
	g_pSceneManager->Add(game);

	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	g_pSceneManager->SwitchTo(main_menu);

	while (!s3eDeviceCheckQuitRequest())
	{
		uint64 new_time = s3eTimerGetMs();

		g_pInput->Update();

		g_pAudio->Update();

		g_pTweener->Update(FRAME_TIME);

		g_pSceneManager->Update(FRAME_TIME);

		Iw2DSurfaceClear(0xff000000);

		g_pSceneManager->Render();

		Iw2DSurfaceShow();

		//int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - new_time));
		//if (yield < 0)
		//	yield = 0;
		s3eDeviceYield();
	}

	delete g_pAudio;
	delete g_pInput;
	delete g_pSceneManager;
	delete g_pTweener;
	delete g_pResources;
	Iw2DTerminate();

	return 0;
}
