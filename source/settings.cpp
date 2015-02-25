#include "settings.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "main.h"
#include "s3eVibra.h"

#include <fstream>

Settings::~Settings()
{
}

void Settings::Init()
{
	Scene::Init();

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
	showOnScreenButtons->m_X = IwGxGetScreenWidth() / 1.5;
	showOnScreenButtons->m_Y = IwGxGetScreenHeight() / 2;
	showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButton());
	showOnScreenButtons->m_W = showOnScreenButtons->GetImage()->GetWidth();
	showOnScreenButtons->m_H = showOnScreenButtons->GetImage()->GetHeight();
	showOnScreenButtons->m_AnchorX = 1;
	showOnScreenButtons->m_AnchorY = 1;
	showOnScreenButtons->m_ScaleX = 0.5;
	showOnScreenButtons->m_ScaleY = 0.5;
	AddChild(showOnScreenButtons);

	backButton = new CSprite();
	backButton->m_X = (float)IwGxGetScreenWidth() / 8;
	backButton->m_Y = (float)IwGxGetScreenHeight() / 8;
	backButton->SetImage(g_pResources->getBackButton());
	backButton->m_W = backButton->GetImage()->GetWidth();
	backButton->m_H = backButton->GetImage()->GetHeight();
	backButton->m_AnchorX = 0.5;
	backButton->m_AnchorY = 0.5;
	backButton->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	backButton->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(backButton);

	Game* game = (Game*)g_pSceneManager->Find("game");
	game->setShowOnScreenButtons(false);

	std::ifstream file("screenbuttons.txt");
	int screenbuttons = 0;
	file >> screenbuttons;
	file.close();
	if (screenbuttons == 1) 
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButtonSelected());
		game->setShowOnScreenButtons(true);
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
				s3eVibraVibrate(60, 125);
				MoveToMainMenu();
			}
			if (showOnScreenButtons->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				s3eVibraVibrate(60, 125);
				SetOnScreenButtons();
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

void Settings::Render()
{
	Scene::Render();
}

void Settings::MoveToMainMenu()
{
	MainMenu* main_menu = (MainMenu*)g_pSceneManager->Find("mainmenu");
	g_pSceneManager->SwitchTo(main_menu);
}