#include "Iw2D.h"
#include "input.h"
#include "audio.h"
#include "scene.h"
#include "game.h"
#include "mainMenu.h"
#include "pauseMenu.h"
#include "resources.h"

#define FRAME_TIME  (30.0f / 1000.0f)

int main()
{
	Iw2DInit();

	g_pResources = new Resources();
	g_pInput = new Input();
	g_pAudio = new Audio();
	g_pSceneManager = new SceneManager();

	Game* game = new Game();
	game->SetName("game");
	game->Init();
	g_pSceneManager->Add(game);
	game->newGame();

	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	PauseMenu* pause_menu = new
	PauseMenu();
	pause_menu->SetName("pausemenu");
	pause_menu->Init();
	g_pSceneManager->Add(pause_menu);

	g_pSceneManager->SwitchTo(main_menu);

	//main game loop
	while(!s3eDeviceCheckQuitRequest())
	{
		g_pInput->Update();
		g_pAudio->Update();
		g_pSceneManager->Update(FRAME_TIME);

		Iw2DSurfaceClear(0xff000000);

		g_pSceneManager->Render();

		Iw2DSurfaceShow();

		s3eDeviceYield(0);
	}

	//clean up
	delete g_pInput;
	delete g_pAudio;
	delete g_pSceneManager;
	delete g_pResources;
	Iw2DTerminate();

	return 0;
}