#include "settings.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "main.h"
#include "vibration.h"

#include <fstream>

Settings::~Settings()
{
}

void Settings::Init()
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

	// Add on screen buttons button
	showOnScreenButtons = new CSprite();
	showOnScreenButtons->m_X = (float)IwGxGetScreenWidth();
	showOnScreenButtons->m_Y = (float)IwGxGetScreenHeight();
	showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButton());
	showOnScreenButtons->m_W = showOnScreenButtons->GetImage()->GetWidth();
	showOnScreenButtons->m_H = showOnScreenButtons->GetImage()->GetHeight();
	showOnScreenButtons->m_AnchorX = 1;
	showOnScreenButtons->m_AnchorY = 7;
	showOnScreenButtons->m_ScaleX = game->getGraphicsScale();
	showOnScreenButtons->m_ScaleY = game->getGraphicsScale();
	AddChild(showOnScreenButtons);

	// Add High Contrast Mode Button
	showHighContrastMode = new CSprite();
	showHighContrastMode->m_X = (float)IwGxGetScreenWidth();
	showHighContrastMode->m_Y = (float)IwGxGetScreenHeight();
	showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButton());
	showHighContrastMode->m_W = showHighContrastMode->GetImage()->GetWidth();
	showHighContrastMode->m_H = showHighContrastMode->GetImage()->GetHeight();
	showHighContrastMode->m_AnchorX = 1;
	showHighContrastMode->m_AnchorY = 5;
	showHighContrastMode->m_ScaleX = game->getGraphicsScale();
	showHighContrastMode->m_ScaleY = game->getGraphicsScale();
	AddChild(showHighContrastMode);

	backButton = new CSprite();
	backButton->m_X = (float)IwGxGetScreenWidth();
	backButton->m_Y = (float)IwGxGetScreenHeight();
	backButton->SetImage(g_pResources->getBackButton());
	backButton->m_W = backButton->GetImage()->GetWidth();
	backButton->m_H = backButton->GetImage()->GetHeight();
	backButton->m_AnchorX = 9.5;
	backButton->m_AnchorY = 20.5;
	backButton->m_ScaleX = game->getGraphicsScale();
	backButton->m_ScaleY = game->getGraphicsScale();
	AddChild(backButton);

	// Checks if the option was selected since the last time the game has been played
	game->setShowOnScreenButtons(false);

	std::ifstream file1("screenbuttons.txt");
	int screenbuttons = 0;
	file1 >> screenbuttons;
	file1.close();
	if (screenbuttons == 1) 
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButtonSelected());
		game->setShowOnScreenButtons(true);
	}

	game->setHighContrastMode(false);

	std::ifstream file2("highcontrastmode.txt");
	int highcontrast = 0;
	file2 >> highcontrast;
	file2.close();
	if (highcontrast == 1){
		showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButtonSelected());
		game->setHighContrastMode(true);
	}

}

void Settings::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->getCurrent() == this)
	{
		// Check if player has pressed and lifted off
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
				SetHighContrastMode();
			}
			g_pInput->Reset();
		}
	}
}

void Settings::SetOnScreenButtons()
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	std::ofstream file;

	if (!game->getShowOnScreenButtons())
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButtonSelected());
		game->setShowOnScreenButtons(true);

		file.open("screenbuttons.txt");
		file << 1;
		file.close();
		
		IwTrace(APP, ("selected on screen buttons option"));
	}
	else
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButton());
		game->setShowOnScreenButtons(false);

		file.open("screenbuttons.txt");
		file << 0;
		file.close();

		IwTrace(APP, ("deselected on screen buttons option"));
	}
}
void Settings::SetHighContrastMode(){
	Game* game = (Game*)g_pSceneManager->Find("game");

	if (!game->getHighContrastMode())
	{
		std::ofstream fileContrastWrite;

		showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButtonSelected());
		game->setHighContrastMode(true);
		game->ChangeBackground();

		fileContrastWrite.open("highcontrastmode.txt");
		fileContrastWrite << 1;
		fileContrastWrite.close();
		
		IwTrace(APP, ("selected on screen buttons option"));
	}
	else
	{
		std::ofstream fileContrastWrite;

		showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButton());
		game->setHighContrastMode(false);
		game->ChangeBackground();

		fileContrastWrite.open("highcontrastmode.txt");
		fileContrastWrite << 0;
		fileContrastWrite.close();

		IwTrace(APP, ("deselected on screen buttons option"));
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