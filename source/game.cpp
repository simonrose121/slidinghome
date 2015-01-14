#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "main.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "pauseMenu.h"
#include "stringExtensions.h"

#define GRID_OFFSET_X		41
#define GRID_OFFSET_Y		37
#define MINIMUM_SWIPE		100
#define SWIPE_OFFSET		200

Game::~Game()
{
	if (grid != 0)
		delete grid;
}

void Game::Init(int grid_width, int grid_height)
{
	Scene::Init();

	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;

	CSprite* background = new CSprite();
	background->m_X = (float)IwGxGetScreenWidth() / 2;
	background->m_Y = (float)IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->GetGameBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	grid = new Grid(this, grid_width, grid_height, (int)(GRID_OFFSET_X * graphicsScale), (int)(GRID_OFFSET_Y * graphicsScale), IwGxGetScreenWidth());
}

void Game::Update(float deltaTime, float alphaMul) 
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();

		//if input is in grid
		if (g_pInput->m_Y >= grid->getGridOriginY())
		{
			IwTrace(Output, ("input detected"));

			//record start position of movement
			int start_x = g_pInput->m_X;
			int start_y = g_pInput->m_Y;

			StringExtensions strEx;

			s = strEx.to_string<int>(start_x);
			char const *x = s.c_str();
			IwTrace(Output, (x)); 

			s = strEx.to_string<int>(start_y);
			char const *y = s.c_str();
			IwTrace(Output, (y));

			//detect swipe
			if (g_pInput->m_X < (start_x - MINIMUM_SWIPE) && g_pInput->m_Y < (start_y + SWIPE_OFFSET) && g_pInput->m_Y < (start_y - SWIPE_OFFSET))
			{
				IwTrace(Output, ("swipe detected"));
			}
		}
	}
}

void Game::Render()
{
	Scene::Render();
}

void Game::newGame()
{

}