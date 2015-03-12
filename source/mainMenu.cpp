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
#include "sound.h"
#include "pauseMenu.h"

#include <fstream>

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

	// Create Sound Button
	soundButtonHome = new CSprite();
	soundButtonHome->SetImage(g_pResources->getSoundButton());
	soundButtonHome->m_X = (float)IwGxGetScreenWidth() / 1.55;
	soundButtonHome->m_Y = (float)IwGxGetScreenHeight() / 1.25;
	soundButtonHome->m_W = soundButtonHome->GetImage()->GetWidth();
	soundButtonHome->m_H = soundButtonHome->GetImage()->GetHeight();
	soundButtonHome->m_AnchorX = 1;
	soundButtonHome->m_AnchorY = 1;
	soundButtonHome->m_ScaleX = game->getGraphicsScale();
	soundButtonHome->m_ScaleY = game->getGraphicsScale();
	AddChild(soundButtonHome);

	// Create Music Button
	musicButtonHome = new CSprite();
	musicButtonHome->SetImage(g_pResources->getMusicButton());
	musicButtonHome->m_X = (float)IwGxGetScreenWidth() / 2.05;
	musicButtonHome->m_Y = (float)IwGxGetScreenHeight() / 1.25;
	musicButtonHome->m_W = musicButtonHome->GetImage()->GetWidth();
	musicButtonHome->m_H = musicButtonHome->GetImage()->GetHeight();
	musicButtonHome->m_AnchorX = 1;
	musicButtonHome->m_AnchorY = 1;
	musicButtonHome->m_ScaleX = game->getGraphicsScale();
	musicButtonHome->m_ScaleY = game->getGraphicsScale();
	AddChild(musicButtonHome);

	
	std::ifstream soundfile("sound.txt");
	int sound = 0;
	soundfile >> sound;
	soundfile.close();
	if (sound == 1){
		soundButtonHome->SetImage(g_pResources->getSoundButton());
		g_pSound->setSoundMode(true);
	}
	else{
		soundButtonHome->SetImage(g_pResources->getSoundButtonOff());
		g_pSound->setSoundMode(false);
	}
	
	std::ifstream musicfile("music.txt");
	int music = 0;
	musicfile >> music;
	musicfile.close();
	if (music == 1){
		musicButtonHome->SetImage(g_pResources->getMusicButton());
		g_pSound->setMusicMode(true);
	}
	else{
		musicButtonHome->SetImage(g_pResources->getMusicButtonOff());
		g_pSound->setMusicMode(false);
	}
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
		else if (soundButtonHome->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			SetSound();
			g_pVibration->Vibrate();
		}
		else if (musicButtonHome->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			SetMusic();
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

void MainMenu::SetSound(){
	std::ofstream soundfile;

	PauseMenu* pause = (PauseMenu*)g_pSceneManager->Find("pause");

	if (!g_pSound->getSound())
	{
		soundButtonHome->SetImage(g_pResources->getSoundButton());
		pause->getSoundButtonPause()->SetImage(g_pResources->getSoundButton());
		g_pSound->setSoundMode(true);

		soundfile.open("sound.txt");
		soundfile << 1;
		soundfile.close();
	}
	else
	{
		soundButtonHome->SetImage(g_pResources->getSoundButtonOff());
		pause->getSoundButtonPause()->SetImage(g_pResources->getSoundButtonOff());
		g_pSound->setSoundMode(false);

		soundfile.open("sound.txt");
		soundfile << 0;
		soundfile.close();
	}
}

void MainMenu::SetMusic(){
	std::ofstream musicfile;
	PauseMenu* pause = (PauseMenu*)g_pSceneManager->Find("pauseMenu");

	if (!g_pSound->getMusic())
	{
		musicButtonHome->SetImage(g_pResources->getMusicButton());
		pause->getMusicButtonPause()->SetImage(g_pResources->getMusicButton());
		g_pSound->setMusicMode(true);
		g_pSound->StartMusic();

		musicfile.open("music.txt");
		musicfile << 1;
		musicfile.close();
	}
	else
	{
		musicButtonHome->SetImage(g_pResources->getMusicButtonOff());
		pause->getMusicButtonPause()->SetImage(g_pResources->getMusicButtonOff());
		g_pSound->setMusicMode(false);
		g_pSound->StopMusic();

		musicfile.open("music.txt");
		musicfile << 0;
		musicfile.close();
	}
}