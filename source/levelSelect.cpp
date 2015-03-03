#include "levelSelect.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "main.h"
#include "vibration.h"

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
	}
}

void LevelSelect::Render()
{
	Scene::Render();
}

void LevelSelect::StartGame(std::string levelNo)
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);

	game->NewGame(levelNo, 13, 14);
}