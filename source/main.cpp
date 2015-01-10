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
	g_pSceneManager = new SceneManager();

	//Game* game = new Game();
	//game->SetName("game");
	//game->Init();
	//g_pSceneManager->Add(game);

	MainMenu* main_menu = new MainMenu();
	main_menu->SetName("mainmenu");
	main_menu->Init();
	g_pSceneManager->Add(main_menu);

	g_pSceneManager->SwitchTo(main_menu);

	while (!s3eDeviceCheckQuitRequest())
	{
		g_pSceneManager->Update(FRAME_TIME);

		Iw2DSurfaceClear(0xff000000);

		g_pSceneManager->Render();

		Iw2DSurfaceShow();

		s3eDeviceYield();
	}

	delete g_pResources;
	delete g_pSceneManager;
	Iw2DTerminate();

	return 0;
}
