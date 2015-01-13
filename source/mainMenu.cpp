#include "mainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"

MainMenu::~MainMenu()
{
}

void MainMenu::startGame(CTween* pTween) 
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);

	//start game music

	//create game
	//game->NewGame();
}

void MainMenu::Update(float deltaTime, float alphaMul) 
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// Detect screen tap
	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			// Animate the play button
			m_Tweener.Tween(0.5f,
				FLOAT, &playText->m_Angle, 360.0f,
				FLOAT, &playText->m_Alpha, 0.3f,
				END);
			m_Tweener.Tween(0.2f,
				FLOAT, &playButton->m_Alpha, 0.3f,
				DELAY, 0.25f,
				EASING, Ease::powIn,
				ONCOMPLETE, startGame,
				END);
		}
	}
}

void MainMenu::Render()
{
	Scene::Render();
}

void MainMenu::Init()
{
	Scene::Init();

	Game* game = (Game*)g_pSceneManager->Find("game");

	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->GetMainMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	float x_pos = (float)IwGxGetScreenWidth() / 2;
	float y_pos = (float)IwGxGetScreenHeight() / 3;
	playButton = new CSprite();
	playButton->SetImage(g_pResources->GetPlayButton());
	playButton->m_X = x_pos;
	playButton->m_Y = y_pos;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 1;
	playButton->m_AnchorY = 1;
	playButton->m_ScaleX = game->getGraphicsScale();
	playButton->m_ScaleY = game->getGraphicsScale();
	AddChild(playButton);
}