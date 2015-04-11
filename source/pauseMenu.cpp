#include "pauseMenu.h"
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

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init()
{
	Scene::Init();

	// get game to access graphics scale
	Game* game = (Game*)g_pSceneManager->Find("game");

	background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getPauseMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	float x_pos = (float)IwGxGetScreenWidth() / 1.4;
	float y_pos = (float)IwGxGetScreenHeight() / 2.75;
	playButton = new CSprite();
	playButton->SetImage(g_pResources->getPlayButtonHC());
	playButton->m_X = x_pos;
	playButton->m_Y = y_pos;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 1;
	playButton->m_AnchorY = 1;
	playButton->m_ScaleX = game->getGraphicsScale();
	playButton->m_ScaleY = game->getGraphicsScale();
	AddChild(playButton);

	float endx_pos = (float)IwGxGetScreenWidth() / 1.4;
	float endy_pos = (float)IwGxGetScreenHeight() / 1.75;
	exitButton = new CSprite();
	exitButton->SetImage(g_pResources->getExitButton());
	exitButton->m_X = endx_pos;
	exitButton->m_Y = endy_pos;
	exitButton->m_W = exitButton->GetImage()->GetWidth();
	exitButton->m_H = exitButton->GetImage()->GetHeight();
	exitButton->m_AnchorX = 1;
	exitButton->m_AnchorY = 1;
	exitButton->m_ScaleX = game->getGraphicsScale();
	exitButton->m_ScaleY = game->getGraphicsScale();
	AddChild(exitButton);

	soundButtonPause = new CSprite();
	soundButtonPause->SetImage(g_pResources->getSoundButton());
	soundButtonPause->m_X = (float)IwGxGetScreenWidth() / 1.55;
	soundButtonPause->m_Y = (float)IwGxGetScreenHeight() / 1.25;
	soundButtonPause->m_W = soundButtonPause->GetImage()->GetWidth();
	soundButtonPause->m_H = soundButtonPause->GetImage()->GetHeight();
	soundButtonPause->m_AnchorX = 1;
	soundButtonPause->m_AnchorY = 1;
	soundButtonPause->m_ScaleX = game->getGraphicsScale();
	soundButtonPause->m_ScaleY = game->getGraphicsScale();
	AddChild(soundButtonPause);

	musicButtonPause = new CSprite();
	musicButtonPause->SetImage(g_pResources->getMusicButton());
	musicButtonPause->m_X = (float)IwGxGetScreenWidth() / 2.05;
	musicButtonPause->m_Y = (float)IwGxGetScreenHeight() / 1.25;
	musicButtonPause->m_W = musicButtonPause->GetImage()->GetWidth();
	musicButtonPause->m_H = musicButtonPause->GetImage()->GetHeight();
	musicButtonPause->m_AnchorX = 1;
	musicButtonPause->m_AnchorY = 1;
	musicButtonPause->m_ScaleX = game->getGraphicsScale();
	musicButtonPause->m_ScaleY = game->getGraphicsScale();
	AddChild(musicButtonPause);

	// check if sound enabled previously and set accordingly
	std::ifstream soundfile("sound.txt");
	int sound = 0;
	soundfile >> sound;
	soundfile.close();
	if (sound == 1)
	{
		soundButtonPause->SetImage(g_pResources->getSoundButton());
		g_pSound->setSoundMode(true);
	}
	else
	{
		soundButtonPause->SetImage(g_pResources->getSoundButtonOff());
		g_pSound->setSoundMode(false);
	}

	// check if music enabled previously and set accordingly
	std::ifstream musicfile("music.txt");
	int music = 0;
	musicfile >> music;
	musicfile.close();
	if (music == 1)
	{
		musicButtonPause->SetImage(g_pResources->getMusicButton());
		g_pSound->setMusicMode(true);
	}
	else
	{
		musicButtonPause->SetImage(g_pResources->getMusicButtonOff());
		g_pSound->setMusicMode(false);
	}
}
void PauseMenu::ChangeBackground()
{
	if (changeToHighContrast)
	{
		background->SetImage(g_pResources->getPauseMenuBGHC());
	}
	else
	{
		background->SetImage(g_pResources->getPauseMenuBG());
	}
}

void PauseMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// detect screen tap
	if (m_IsInputActive && m_Manager->getCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		if (exitButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			mainMenu();
		}
		if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			g_pVibration->Vibrate();
			StartGame();
		}
		else if (soundButtonPause->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			SetSound();
			g_pVibration->Vibrate();
		}
		else if (musicButtonPause->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			SetMusic();
			g_pVibration->Vibrate();
		}
		g_pInput->Reset();
	}
}

void PauseMenu::Render()
{
	Scene::Render();
}

void PauseMenu::StartGame() 
{
	// move back to game scene
	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);
}

void PauseMenu::mainMenu()
{
	// end game and move to main menu
	MainMenu* mainmenu = (MainMenu*)g_pSceneManager->Find("mainmenu");
	Game* game = (Game*)g_pSceneManager->Find("game");
	
	game->EndGame();
	g_pSceneManager->SwitchTo(mainmenu);
}

void PauseMenu::SetSound()
{
	// update sound file
	std::ofstream soundfile;
	MainMenu* mainmenu = (MainMenu*)g_pSceneManager->Find("mainmenu");

	if (!g_pSound->getSound())
	{
		soundButtonPause->SetImage(g_pResources->getSoundButton());
		mainmenu->getSoundButtonHome()->SetImage(g_pResources->getSoundButton());
		g_pSound->setSoundMode(true);

		soundfile.open("sound.txt");
		soundfile << 1;
		soundfile.close();
	}
	else
	{
		soundButtonPause->SetImage(g_pResources->getSoundButtonOff());
		mainmenu->getSoundButtonHome()->SetImage(g_pResources->getSoundButtonOff());
		g_pSound->setSoundMode(false);

		soundfile.open("sound.txt");
		soundfile << 0;
		soundfile.close();
	}
}

void PauseMenu::SetMusic()
{
	// update music file
	std::ofstream musicfile;
	MainMenu* mainmenu = (MainMenu*)g_pSceneManager->Find("mainmenu");

	if (!g_pSound->getMusic())
	{
		musicButtonPause->SetImage(g_pResources->getMusicButton());
		mainmenu->getMusicButtonHome()->SetImage(g_pResources->getMusicButton());
		g_pSound->setMusicMode(true);
		g_pSound->StartMusic();

		musicfile.open("music.txt");
		musicfile << 1;
		musicfile.close();
	}
	else
	{
		musicButtonPause->SetImage(g_pResources->getMusicButtonOff());
		mainmenu->getMusicButtonHome()->SetImage(g_pResources->getMusicButtonOff());
		g_pSound->setMusicMode(false);
		g_pSound->StopMusic();

		musicfile.open("music.txt");
		musicfile << 0;
		musicfile.close();
	}
}