#include "settings.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "pauseMenu.h"
#include "main.h"
#include "vibration.h"
#include "sound.h"
#include "levelSelect.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>

Settings::~Settings()
{
}

void Settings::Init()
{
	Scene::Init();

	Game* game = (Game*)g_pSceneManager->Find("game");

	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getEndScreenBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	showOnScreenButtons = new CSprite();
	showOnScreenButtons->m_X = IwGxGetScreenWidth() / 2;
	showOnScreenButtons->m_Y = IwGxGetScreenHeight() / 5;
	showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButton());
	showOnScreenButtons->m_W = showOnScreenButtons->GetImage()->GetWidth();
	showOnScreenButtons->m_H = showOnScreenButtons->GetImage()->GetHeight();
	showOnScreenButtons->m_AnchorX = 0.5;
	showOnScreenButtons->m_AnchorY = 0.5;
	showOnScreenButtons->m_ScaleX = game->getGraphicsScale();
	showOnScreenButtons->m_ScaleY = game->getGraphicsScale();
	AddChild(showOnScreenButtons);

	showHighContrastMode = new CSprite();
	showHighContrastMode->m_X = IwGxGetScreenWidth() / 2;
	showHighContrastMode->m_Y = IwGxGetScreenHeight() / 2.85;
	showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButton());
	showHighContrastMode->m_W = showHighContrastMode->GetImage()->GetWidth();
	showHighContrastMode->m_H = showHighContrastMode->GetImage()->GetHeight();
	showHighContrastMode->m_AnchorX = 0.5;
	showHighContrastMode->m_AnchorY = 0.5;
	showHighContrastMode->m_ScaleX = game->getGraphicsScale();
	showHighContrastMode->m_ScaleY = game->getGraphicsScale();
	AddChild(showHighContrastMode);

	showVibration = new CSprite();
	showVibration->m_X = IwGxGetScreenWidth() / 2;
	showVibration->m_Y = IwGxGetScreenHeight() / 2;
	showVibration->SetImage(g_pResources->getVibrationSettingButton());
	showVibration->m_W = showVibration->GetImage()->GetWidth();
	showVibration->m_H = showVibration->GetImage()->GetHeight();
	showVibration->m_AnchorX = 0.5;
	showVibration->m_AnchorY = 0.5;
	showVibration->m_ScaleX = game->getGraphicsScale();
	showVibration->m_ScaleY = game->getGraphicsScale();
	AddChild(showVibration);

	backButton = new CSprite();
	backButton->m_X = IwGxGetDisplayWidth() / 15;
	backButton->m_Y = IwGxGetScreenHeight() / 25;
	backButton->SetImage(g_pResources->getBackButton());
	backButton->m_W = backButton->GetImage()->GetWidth();
	backButton->m_H = backButton->GetImage()->GetHeight();
	backButton->m_AnchorX = 0.5;
	backButton->m_AnchorY = 0.5;
	backButton->m_ScaleX = game->getGraphicsScale();
	backButton->m_ScaleY = game->getGraphicsScale();
	AddChild(backButton);

	reset = new CSprite();
	reset->m_X = IwGxGetDisplayWidth() / 1.1;
	reset->m_Y = IwGxGetScreenHeight() / 25;
	reset->SetImage(g_pResources->getResetLevels());
	reset->m_W = reset->GetImage()->GetWidth();
	reset->m_H = reset->GetImage()->GetHeight();
	reset->m_AnchorX = 0.5;
	reset->m_AnchorY = 0.5;
	reset->m_ScaleX = game->getGraphicsScale();
	reset->m_ScaleY = game->getGraphicsScale();
	AddChild(reset);

	// checks if the option was selected since the last time the game has been played
	game->setShowOnScreenButtons(false);
	std::ifstream screenbuttonfile("screenbuttons.txt");
	int screenbuttons = 0;
	screenbuttonfile >> screenbuttons;
	screenbuttonfile.close();
	if (screenbuttons == 1) 
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButtonSelected());
		game->setShowOnScreenButtons(true);
	}

	// check high contrast mode
	game->setHighContrastMode(false);
	MainMenu* menu = (MainMenu*)g_pSceneManager->Find("mainMenu");
	PauseMenu* pause = (PauseMenu*)g_pSceneManager->Find("pauseMenu");
	std::ifstream highcontrastfile("highcontrastmode.txt");
	int highcontrast = 0;
	highcontrastfile >> highcontrast;
	highcontrastfile.close();
	if (highcontrast == 1){
		showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButtonSelected());
		game->setHighContrastMode(true);
		menu->setHighContrastMode(true);
		pause->setHighContrastMode(true);
		game->ChangeBackground();
		menu->ChangeBackground();
		pause->ChangeBackground();
	}

	// check vibration mode
	g_pVibration->setVibrationMode(false);
	std::ifstream vibrationfile("vibration.txt");
	int vibration = 0;
	vibrationfile >> vibration;
	vibrationfile.close();
	if (vibration == 1){
		showVibration->SetImage(g_pResources->getVibrationSettingButtonSelected());
		g_pVibration->setVibrationMode(true);
	}
}

void Settings::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// detect screen tap
	if (m_IsInputActive && m_Manager->getCurrent() == this)
	{
		if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			if (backButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				MoveToMainMenu();
			}
			if (showOnScreenButtons->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				SetOnScreenButtons();
			}
			if (showHighContrastMode->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				SetHighContrastMode();
			}
			if (showVibration->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				SetVibrationOn();
			}
			if (reset->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				ResetGame();
			}
			g_pInput->Reset();
		}
	}
}

void Settings::SetOnScreenButtons()
{
	// set on screen buttons setting
	Game* game = (Game*)g_pSceneManager->Find("game");
	std::ofstream file;

	if (!game->getShowOnScreenButtons())
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButtonSelected());
		game->setShowOnScreenButtons(true);

		file.open("screenbuttons.txt");
		file << 1;
		file.close();
	}
	else
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButton());
		game->setShowOnScreenButtons(false);

		file.open("screenbuttons.txt");
		file << 0;
		file.close();
	}
}

void Settings::SetHighContrastMode()
{
	// set high contrast setting
	Game* game = (Game*)g_pSceneManager->Find("game");
	MainMenu* menu = (MainMenu*)g_pSceneManager->Find("mainMenu");
	PauseMenu* pause = (PauseMenu*)g_pSceneManager->Find("pauseMenu");

	if (!game->getHighContrastMode())
	{
		std::ofstream fileContrastWrite;

		showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButtonSelected());
		game->setHighContrastMode(true);
		menu->setHighContrastMode(true);
		pause->setHighContrastMode(true);
		game->ChangeBackground();
		menu->ChangeBackground();
		pause->ChangeBackground();

		fileContrastWrite.open("highcontrastmode.txt");
		fileContrastWrite << 1;
		fileContrastWrite.close();
	}
	else
	{
		std::ofstream fileContrastWrite;

		showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButton());
		game->setHighContrastMode(false);
		menu->setHighContrastMode(false);
		pause->setHighContrastMode(false);
		game->ChangeBackground();
		menu->ChangeBackground();
		pause->ChangeBackground();

		fileContrastWrite.open("highcontrastmode.txt");
		fileContrastWrite << 0;
		fileContrastWrite.close();
	}
}

void Settings::SetVibrationOn()
{
	// set vibration setting
	if (!g_pVibration->getVibration())
	{
		std::ofstream fileVibrationWrite;

		showVibration->SetImage(g_pResources->getVibrationSettingButtonSelected());
		g_pVibration->setVibrationMode(true);

		fileVibrationWrite.open("vibration.txt");
		fileVibrationWrite << 1;
		fileVibrationWrite.close();
	}
	else
	{
		std::ofstream fileVibrationWrite;

		showVibration->SetImage(g_pResources->getVibrationSettingButton());
		g_pVibration->setVibrationMode(false);

		fileVibrationWrite.open("vibration.txt");
		fileVibrationWrite << 0;
		fileVibrationWrite.close();
	}
}

void Settings::Render()
{
	Scene::Render();
}

void Settings::MoveToMainMenu()
{
	MainMenu* main_menu = (MainMenu*)g_pSceneManager->Find("mainmenu");
	g_pSceneManager->SwitchTo(main_menu);
}

void Settings::ResetGame()
{
	// reset all levels to not complete
	for (int levelNo(1); levelNo <= LEVEL_COUNT; levelNo++)
	{
		std::string levelNoVal;
		std::ostringstream convert;
		convert << levelNo;
		levelNoVal = convert.str();

		// set level to incomplete
		std::string filename = "star" + levelNoVal;
		filename += ".txt";
		std::ofstream file(filename.c_str());
		file << 0;
		file.close();
	}

	LevelSelect* level_select = (LevelSelect*)g_pSceneManager->Find("levelselect");
	// update completed level stars
	level_select->LevelStars();
}