#include "mainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "main.h"
#include "levelSelect.h"
#include "settings.h"
#include "vibration.h"

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	Scene::Init();

	Game* game = (Game*)g_pSceneManager->Find("game");

	// Create menu background
	background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getMainMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	// Create Start Game button
	playButton = new CSprite();
	playButton->SetImage(g_pResources->getPlayButtonHC());
	playButton->m_X = (float)IwGxGetScreenWidth() / 1.3;
	playButton->m_Y = (float)IwGxGetScreenHeight() / 1.8;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 1;
	playButton->m_AnchorY = 1;
	playButton->m_ScaleX = game->getGraphicsScale();
	playButton->m_ScaleY = game->getGraphicsScale();
	AddChild(playButton);

	// Create settings
	settingsButton = new CSprite();
	settingsButton->SetImage(g_pResources->getSettingsButtonHC());
	settingsButton->m_X = (float)IwGxGetScreenWidth() / 1.42;
	settingsButton->m_Y = (float)IwGxGetScreenHeight() / 1.48;
	settingsButton->m_W = settingsButton->GetImage()->GetWidth();
	settingsButton->m_H = settingsButton->GetImage()->GetHeight();
	settingsButton->m_AnchorX = 1;
	settingsButton->m_AnchorY = 1;
	settingsButton->m_ScaleX = game->getGraphicsScale();
	settingsButton->m_ScaleY = game->getGraphicsScale();
	AddChild(settingsButton);
}

void MainMenu::ChangeBackground(){
	if (changeToHighContrast){
		background->SetImage(g_pResources->getMainMenuBGHC());
	}
	else{
		background->SetImage(g_pResources->getMainMenuBG());
	}
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->getCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			MoveToLevelSelect();
			g_pVibration->Vibrate();
			// Start playing game music here
			//Audio::PlayMusic("audio/in_game.mp3", true);
		}
		else if (settingsButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			MoveToSettings();
			g_pVibration->Vibrate();
		}
	}
}

void MainMenu::Render()
{
	Scene::Render();
}

void MainMenu::MoveToLevelSelect()
{
	LevelSelect* levelselect = (LevelSelect*)g_pSceneManager->Find("levelselect");
	g_pSceneManager->SwitchTo(levelselect);
}

void MainMenu::MoveToSettings()
{
	Settings* settings = (Settings*)g_pSceneManager->Find("settings");
	g_pSceneManager->SwitchTo(settings);
}