#include "pauseMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "main.h"

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Init()
{
	Scene::Init();

	Game* game = (Game*)g_pSceneManager->Find("game");

	// Create menu background
	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getPauseMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	// Create Start Game button
	float x_pos = (float)IwGxGetScreenWidth() / 2;
	float y_pos = (float)IwGxGetScreenHeight() / 3;
	playButton = new CSprite();
	playButton->SetImage(g_pResources->getPlayButton());
	playButton->m_X = x_pos;
	playButton->m_Y = y_pos;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 1;
	playButton->m_AnchorY = 1;
	playButton->m_ScaleX = game->getGraphicsScale();
	playButton->m_ScaleY = game->getGraphicsScale();
	AddChild(playButton);

	// Create End Game button
	float endx_pos = (float)IwGxGetScreenWidth() / 2;
	float endy_pos = (float)IwGxGetScreenHeight() / 2;
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
}

void PauseMenu::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->getCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		if (exitButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			mainMenu();
		}
		if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			StartGame();
		}
	}
}

void PauseMenu::Render()
{
	Scene::Render();
}

void PauseMenu::StartGame() 
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);
}

void PauseMenu::mainMenu()
{
	MainMenu* mainmenu = (MainMenu*)g_pSceneManager->Find("mainmenu");
	g_pSceneManager->SwitchTo(mainmenu);

}