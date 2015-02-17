#include "levelSelect.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "mainMenu.h"
#include "main.h"

LevelSelect::~LevelSelect()
{
}

void LevelSelect::Init()
{
	Scene::Init();

	Game* game = (Game*)g_pSceneManager->Find("game");
	levelCount = 4;

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
	for (int i(1); i <= levelCount; ++i)
	{
		float x_pos = (float)IwGxGetScreenWidth() * 1;
		float y_pos = (float)IwGxGetScreenHeight() * 1;
		levelButton = new CSprite();
		levelButton->SetImage(g_pResources->getLevelButton());
		levelButton->m_X = x_pos;
		levelButton->m_Y = y_pos;
		levelButton->m_W = levelButton->GetImage()->GetWidth();
		levelButton->m_H = levelButton->GetImage()->GetHeight();
		levelButton->m_AnchorX = (i * 1.25);
		levelButton->m_AnchorY = 8.5;
		levelButton->m_ScaleX = game->getGraphicsScale();
		levelButton->m_ScaleY = game->getGraphicsScale();
		IwTrace(APP, ("i am being placed at %f, %f", levelButton->m_AnchorX, levelButton->m_AnchorY));
		AddChild(levelButton);

		levelLabel = new CLabel();
		levelLabel->m_X = (float)IwGxGetScreenWidth() * 1;
		levelLabel->m_Y = (float)IwGxGetScreenHeight() * 1;
		levelLabel->m_W = FONT_DESIGN_WIDTH;
		levelLabel->m_H = actualFontHeight;
		levelLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
		levelLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
		levelLabel->m_Font = g_pResources->getFont();
		levelLabel->m_AnchorX = 1.25;
		levelLabel->m_AnchorY = 8.5;
		levelLabel->m_ScaleX = fontScale;
		levelLabel->m_ScaleY = fontScale;
		IwTrace(APP, ("text being placed at %f, %f", levelLabel->m_AnchorX, levelLabel->m_AnchorY));
		AddChild(levelLabel);

		char str[16];
		snprintf(str, 16, "%d", i);
		levelLabel->m_Text = str;
	}

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
		if (levelButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			StartGame();

			// Start playing game music here
			//Audio::PlayMusic("audio/in_game.mp3", true);
		}
	}
}

void LevelSelect::Render()
{
	Scene::Render();
}

void LevelSelect::StartGame()
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);

	//game->newGame();
}