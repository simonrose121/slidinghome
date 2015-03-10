#include "Iw2D.h"
#include "IwTween.h"
#include "input.h"
#include "audio.h"
#include "scene.h"
#include "game.h"
#include "levelSelect.h"
#include "mainMenu.h"
#include "pauseMenu.h"
#include "settings.h"
#include "resources.h"
#include "vibration.h"
#include "sound.h"

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
	g_pVibration = new Vibration(60, 125);
	g_pSound = new Sound();

	Game* game = new Game();
	game->setName("game");
	game->Init();
	g_pSceneManager->Add(game);

	MainMenu* main_menu = new MainMenu();
	main_menu->setName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	LevelSelect* level_select = new LevelSelect();
	level_select->setName("levelselect");
	level_select->Init();
	g_pSceneManager->Add(level_select);

	PauseMenu* pause_menu = new PauseMenu();
	pause_menu->setName("pausemenu");
	pause_menu->Init();
	g_pSceneManager->Add(pause_menu);

	Settings* settings = new Settings();
	settings->setName("settings");
	settings->Init();
	g_pSceneManager->Add(settings);

	g_pSceneManager->SwitchTo(main_menu);

	if (g_pSound->getMusic())
	{
		g_pSound->StartMusic();
	}


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

		int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - new_time));
		if (yield < 0)
			yield = 0;
		s3eDeviceYield(yield);
	}

	delete g_pAudio;
	delete g_pInput;
	delete g_pSceneManager;
	delete g_pTweener;
	delete g_pResources;
	delete g_pVibration;
	delete g_pSound;
	Iw2DTerminate();

	return 0;
}
