#include "settings.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "main.h"
#include "vibration.h"
#include "sound.h"

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
	showOnScreenButtons->m_X = IwGxGetScreenWidth();
	showOnScreenButtons->m_Y = IwGxGetScreenHeight();
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
	showHighContrastMode->m_X = IwGxGetScreenWidth();
	showHighContrastMode->m_Y = IwGxGetScreenHeight();
	showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButton());
	showHighContrastMode->m_W = showHighContrastMode->GetImage()->GetWidth();
	showHighContrastMode->m_H = showHighContrastMode->GetImage()->GetHeight();
	showHighContrastMode->m_AnchorX = 1;
	showHighContrastMode->m_AnchorY = 5;
	showHighContrastMode->m_ScaleX = game->getGraphicsScale();
	showHighContrastMode->m_ScaleY = game->getGraphicsScale();
	AddChild(showHighContrastMode);

	// Add Vibration On Button
	showVibration = new CSprite();
	showVibration->m_X = IwGxGetScreenWidth();
	showVibration->m_Y = IwGxGetScreenWidth();
	showVibration->SetImage(g_pResources->getVibrationSettingButton());
	showVibration->m_W = showVibration->GetImage()->GetWidth();
	showVibration->m_H = showVibration->GetImage()->GetHeight();
	showVibration->m_AnchorX = 1;
	showVibration->m_AnchorY = 3;
	showVibration->m_ScaleX = game->getGraphicsScale();
	showVibration->m_ScaleY = game->getGraphicsScale();
	AddChild(showVibration);

	// Add Sounds on button
	showSound = new CSprite();
	showSound->m_X = IwGxGetScreenWidth();
	showSound->m_Y = IwGxGetScreenWidth();
	showSound->SetImage(g_pResources->getSoundSettingButton());
	showSound->m_W = showSound->GetImage()->GetWidth();
	showSound->m_H = showSound->GetImage()->GetHeight();
	showSound->m_AnchorX = 1;
	showSound->m_AnchorY = 1;
	showSound->m_ScaleX = game->getGraphicsScale();
	showSound->m_ScaleY = game->getGraphicsScale();
	AddChild(showSound);

	// Add Music on button
	showMusic = new CSprite();
	showMusic->m_X = IwGxGetScreenWidth();
	showMusic->m_Y = IwGxGetScreenWidth();
	showMusic->SetImage(g_pResources->getMusicSettingButton());
	showMusic->m_W = showMusic->GetImage()->GetWidth();
	showMusic->m_H = showMusic->GetImage()->GetHeight();
	showMusic->m_AnchorX = 1;
	showMusic->m_AnchorY = 0.25;
	showMusic->m_ScaleX = game->getGraphicsScale();
	showMusic->m_ScaleY = game->getGraphicsScale();
	AddChild(showMusic);

	backButton = new CSprite();
	backButton->m_X = IwGxGetScreenWidth();
	backButton->m_Y = IwGxGetScreenHeight();
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

	std::ifstream screenbuttonfile("screenbuttons.txt");
	int screenbuttons = 0;
	screenbuttonfile >> screenbuttons;
	screenbuttonfile.close();
	if (screenbuttons == 1) 
	{
		showOnScreenButtons->SetImage(g_pResources->getOnScreenSettingButtonSelected());
		game->setShowOnScreenButtons(true);
	}

	game->setHighContrastMode(false);

	std::ifstream highcontrastfile("highcontrastmode.txt");
	int highcontrast = 0;
	highcontrastfile >> highcontrast;
	highcontrastfile.close();
	if (highcontrast == 1){
		showHighContrastMode->SetImage(g_pResources->getHighContrastSettingButtonSelected());
		game->setHighContrastMode(true);
	}

	g_pVibration->setVibrationMode(false);

	std::ifstream vibrationfile("vibration.txt");
	int vibration = 0;
	vibrationfile >> vibration;
	vibrationfile.close();
	if (vibration == 1){
		showVibration->SetImage(g_pResources->getVibrationSettingButtonSelected());
		g_pVibration->setVibrationMode(true);
	}

	g_pSound->setSoundMode(false);
	std::ifstream soundfile("sound.txt");
	int sound = 0;
	soundfile >> sound;
	soundfile.close();
	if (sound == 1){
		showSound->SetImage(g_pResources->getSoundSettingButtonSelected());
		g_pSound->setSoundMode(true);
	}

	g_pSound->setMusicMode(false);
	std::ifstream musicfile("music.txt");
	int music = 0;
	musicfile >> sound;
	musicfile.close();
	if (music == 1){
		showSound->SetImage(g_pResources->getSoundSettingButtonSelected());
		g_pSound->setMusicMode(true);
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
				g_pVibration->Vibrate();
				SetHighContrastMode();
			}
			if (showVibration->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				SetVibrationOn();
			}
			if (showSound->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				SetSound();
			}
			if (showMusic->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				g_pVibration->Vibrate();
				SetMusic();
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
	}
}

void Settings::SetVibrationOn(){
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

void Settings::SetSound()
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	std::ofstream soundfile;

	if (!g_pSound->getSound())
	{
		showSound->SetImage(g_pResources->getSoundSettingButtonSelected());
		g_pSound->setSoundMode(true);

		soundfile.open("sound.txt");
		soundfile << 1;
		soundfile.close();
	}
	else
	{
		showSound->SetImage(g_pResources->getSoundSettingButton());
		g_pSound->setSoundMode(false);

		soundfile.open("sound.txt");
		soundfile << 0;
		soundfile.close();
	}
}

void Settings::SetMusic()
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	std::ofstream musicfile;

	if (!g_pSound->getMusic())
	{
		showMusic->SetImage(g_pResources->getMusicSettingButtonSelected());
		g_pSound->setMusicMode(true);
		g_pSound->StartMusic();

		musicfile.open("music.txt");
		musicfile << 1;
		musicfile.close();
	}
	else
	{
		showMusic->SetImage(g_pResources->getMusicSettingButton());
		g_pSound->setMusicMode(false);
		g_pSound->StopMusic();

		musicfile.open("music.txt");
		musicfile << 0;
		musicfile.close();
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