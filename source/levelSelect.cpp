#include "levelSelect.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "main.h"
#include "vibration.h"
#include "s3eVideo.h"
#include <sstream>

#include <iostream>
#include <fstream>

LevelSelect::~LevelSelect()
{
}

void LevelSelect::Init()
{
	Scene::Init();

	Game* game = (Game*)g_pSceneManager->Find("game");

	// Create menu background
	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getEndScreenBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	//Buttons for levels need to be added here
	// Create Start Game button
	float x_pos = (float)IwGxGetScreenWidth();
	float y_pos = (float)IwGxGetScreenHeight();

	level1 = new CSprite();
	level1->SetImage(g_pResources->getLevel1());
	level1->m_X = x_pos;
	level1->m_Y = y_pos;
	level1->m_W = level1->GetImage()->GetWidth();
	level1->m_H = level1->GetImage()->GetHeight();
	level1->m_AnchorX = 5.75;
	level1->m_AnchorY = 8.5;
	level1->m_ScaleX = game->getGraphicsScale();
	level1->m_ScaleY = game->getGraphicsScale();
	AddChild(level1);

	level2 = new CSprite();
	level2->SetImage(g_pResources->getLevel2());
	level2->m_X = x_pos;
	level2->m_Y = y_pos;
	level2->m_W = level2->GetImage()->GetWidth();
	level2->m_H = level2->GetImage()->GetHeight();
	level2->m_AnchorX = 4.25;
	level2->m_AnchorY = 8.5;
	level2->m_ScaleX = game->getGraphicsScale();
	level2->m_ScaleY = game->getGraphicsScale();
	AddChild(level2);

	level3 = new CSprite();
	level3->SetImage(g_pResources->getLevel3());
	level3->m_X = x_pos;
	level3->m_Y = y_pos;
	level3->m_W = level3->GetImage()->GetWidth();
	level3->m_H = level3->GetImage()->GetHeight();
	level3->m_AnchorX = 2.75;
	level3->m_AnchorY = 8.5;
	level3->m_ScaleX = game->getGraphicsScale();
	level3->m_ScaleY = game->getGraphicsScale();
	AddChild(level3);

	level4 = new CSprite();
	level4->SetImage(g_pResources->getLevel4());
	level4->m_X = x_pos;
	level4->m_Y = y_pos;
	level4->m_W = level4->GetImage()->GetWidth();
	level4->m_H = level4->GetImage()->GetHeight();
	level4->m_AnchorX = 1.25;
	level4->m_AnchorY = 8.5;
	level4->m_ScaleX = game->getGraphicsScale();
	level4->m_ScaleY = game->getGraphicsScale();
	AddChild(level4);

	level5 = new CSprite();
	level5->SetImage(g_pResources->getLevel5());
	level5->m_X = x_pos;
	level5->m_Y = y_pos;
	level5->m_W = level5->GetImage()->GetWidth();
	level5->m_H = level5->GetImage()->GetHeight();
	level5->m_AnchorX = 5.75;
	level5->m_AnchorY = 7;
	level5->m_ScaleX = game->getGraphicsScale();
	level5->m_ScaleY = game->getGraphicsScale();
	AddChild(level5);

	level6 = new CSprite();
	level6->SetImage(g_pResources->getLevel6());
	level6->m_X = x_pos;
	level6->m_Y = y_pos;
	level6->m_W = level6->GetImage()->GetWidth();
	level6->m_H = level6->GetImage()->GetHeight();
	level6->m_AnchorX = 4.25;
	level6->m_AnchorY = 7;
	level6->m_ScaleX = game->getGraphicsScale();
	level6->m_ScaleY = game->getGraphicsScale();
	AddChild(level6);

	level7 = new CSprite();
	level7->SetImage(g_pResources->getLevel7());
	level7->m_X = x_pos;
	level7->m_Y = y_pos;
	level7->m_W = level7->GetImage()->GetWidth();
	level7->m_H = level7->GetImage()->GetHeight();
	level7->m_AnchorX = 2.75;
	level7->m_AnchorY = 7;
	level7->m_ScaleX = game->getGraphicsScale();
	level7->m_ScaleY = game->getGraphicsScale();
	AddChild(level7);

	level8 = new CSprite();
	level8->SetImage(g_pResources->getLevel8());
	level8->m_X = x_pos;
	level8->m_Y = y_pos;
	level8->m_W = level8->GetImage()->GetWidth();
	level8->m_H = level8->GetImage()->GetHeight();
	level8->m_AnchorX = 1.25;
	level8->m_AnchorY = 7;
	level8->m_ScaleX = game->getGraphicsScale();
	level8->m_ScaleY = game->getGraphicsScale();
	AddChild(level8);

	level9 = new CSprite();
	level9->SetImage(g_pResources->getLevel9());
	level9->m_X = x_pos;
	level9->m_Y = y_pos;
	level9->m_W = level9->GetImage()->GetWidth();
	level9->m_H = level9->GetImage()->GetHeight();
	level9->m_AnchorX = 5.75;
	level9->m_AnchorY = 5.5;
	level9->m_ScaleX = game->getGraphicsScale();
	level9->m_ScaleY = game->getGraphicsScale();
	AddChild(level9);

	level10 = new CSprite();
	level10->SetImage(g_pResources->getLevel10());
	level10->m_X = x_pos;
	level10->m_Y = y_pos;
	level10->m_W = level10->GetImage()->GetWidth();
	level10->m_H = level10->GetImage()->GetHeight();
	level10->m_AnchorX = 4.25;
	level10->m_AnchorY = 5.5;
	level10->m_ScaleX = game->getGraphicsScale();
	level10->m_ScaleY = game->getGraphicsScale();
	AddChild(level10);

	level11 = new CSprite();
	level11->SetImage(g_pResources->getLevel11());
	level11->m_X = x_pos;
	level11->m_Y = y_pos;
	level11->m_W = level11->GetImage()->GetWidth();
	level11->m_H = level11->GetImage()->GetHeight();
	level11->m_AnchorX = 2.75;
	level11->m_AnchorY = 5.5;
	level11->m_ScaleX = game->getGraphicsScale();
	level11->m_ScaleY = game->getGraphicsScale();
	AddChild(level11);

	level12 = new CSprite();
	level12->SetImage(g_pResources->getLevel12());
	level12->m_X = x_pos;
	level12->m_Y = y_pos;
	level12->m_W = level12->GetImage()->GetWidth();
	level12->m_H = level12->GetImage()->GetHeight();
	level12->m_AnchorX = 1.25;
	level12->m_AnchorY = 5.5;
	level12->m_ScaleX = game->getGraphicsScale();
	level12->m_ScaleY = game->getGraphicsScale();
	AddChild(level12);

	//Back button
	backButton = new CSprite();
	backButton->m_X = IwGxGetScreenWidth();
	backButton->m_Y = IwGxGetScreenHeight();
	backButton->SetImage(g_pResources->getBackButton());
	backButton->m_W = backButton->GetImage()->GetWidth();
	backButton->m_H = backButton->GetImage()->GetHeight();
	backButton->m_AnchorX = 9.75;
	backButton->m_AnchorY = 20.85;
	backButton->m_ScaleX = game->getGraphicsScale();
	backButton->m_ScaleY = game->getGraphicsScale();
	AddChild(backButton);

	hasStars = false;
	LevelStars();
}

void LevelSelect::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->getCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		if (backButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			MoveToMainMenu();
		}
		if (level1->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("1");
		}
		if (level2->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("2");
		}
		if (level3->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("3");
		}
		if (level4->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("4");
		}
		if (level5->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("5");
		}
		if (level6->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("6");
		}
		if (level7->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("7");
		}
		if (level8->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("8");
		}
		if (level9->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("9");
		}
		if (level10->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("10");
		}
		if (level11->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("11");
		}
		if (level12->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame("12");
		}
	}

}

void LevelSelect::Render()
{
	//s3eVideoPlay("videos/intromovie.mp4", 1, 0, 0, 200, 150);
	//if (s3eVideoIsPlaying() == S3E_FALSE)
	//{
		Scene::Render();
	//}
}

void LevelSelect::StartGame(std::string levelNo)
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);

	game->NewGame(levelNo, 12, 14);
}

void LevelSelect::MoveToMainMenu()
{
	MainMenu* main_menu = (MainMenu*)g_pSceneManager->Find("mainmenu");
	g_pSceneManager->SwitchTo(main_menu);
}

void LevelSelect::LevelStars()
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	int row = 0;
	for (int levelNo(1); levelNo <= LEVEL_COUNT; levelNo++)
	{
		std::string levelNoVal;
		std::ostringstream convert;
		convert << levelNo;
		levelNoVal = convert.str();

		//Star complete
		std::string filename = "star" + levelNoVal;
		filename += ".txt";
		std::ifstream file(filename.c_str());
		int fileNumber = 0;
		file >> fileNumber;
		file.close();
		if (fileNumber == 1)
		{
			star = new CSprite();
			star->SetImage(g_pResources->getStar());
			star->m_X = (float)IwGxGetScreenWidth();
			star->m_Y = (float)IwGxGetScreenHeight();
			star->m_W = star->GetImage()->GetWidth();
			star->m_H = star->GetImage()->GetHeight();
			float x = 11 - (((levelNo - 1) % 4) * 3);
			float y = 16.5 - ((4 * row) / 1.35);
			IwTrace(APP, ("level %d, position %f, %f", levelNo, x, y));
			star->m_AnchorX = x;
			star->m_AnchorY = y;
			star->m_ScaleX = game->getGraphicsScale();
			star->m_ScaleY = game->getGraphicsScale();
			AddChild(star);
			hasStars = true;
		}
		if ((levelNo % 4) == 0)
		{
			row++;
		}
	}
}

void LevelSelect::RemoveLevelStars()
{
	if (hasStars) 
	{
		this->RemoveChild(star);
		delete star;
	}
}