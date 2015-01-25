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

void Game::Init(int width, int height)
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

	grid = new Grid(this, width, height, (int)(GRID_OFFSET_X * graphicsScale), (int)(GRID_OFFSET_Y * graphicsScale), IwGxGetScreenWidth());
}

void Game::Update(float deltaTime, float alphaMul) 
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	if (m_IsInputActive && m_Manager->GetCurrent() == this)
	{
		//if input is in grid
		if (g_pInput->m_Y >= grid->getGridOriginY())
		{
			if (!g_pInput->m_Touched && !g_pInput->m_PrevTouched)
			{
				//record start position of movement
				start_x = g_pInput->m_X;
				start_y = g_pInput->m_Y;
			}
			else if (g_pInput->m_Touched && !g_pInput->m_PrevTouched)
			{
				IwTrace(APP, ("currently pressing down"));

				IwTrace(APP, ("start x,y = %d,%d current x,y = %d,%d", start_x, start_y, g_pInput->m_X, g_pInput->m_Y));
			}
			else if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				if (g_pInput->m_X < start_x - MINIMUM_SWIPE && g_pInput->m_Y < start_y + SWIPE_OFFSET && g_pInput->m_Y > start_y - SWIPE_OFFSET)
				{
					IwTrace(APP, ("move left"));
					grid->movePlayerLeft();
				}
				if (g_pInput->m_Y < start_y - MINIMUM_SWIPE && g_pInput->m_X < start_x + SWIPE_OFFSET && g_pInput->m_X > start_x - SWIPE_OFFSET)
				{
					IwTrace(APP, ("move up"));
				}
				if (g_pInput->m_X > start_x + MINIMUM_SWIPE && g_pInput->m_Y < start_y + SWIPE_OFFSET && g_pInput->m_Y > start_y - SWIPE_OFFSET)
				{
					IwTrace(APP, ("move right"));
					grid->movePlayerRight();
				}
				if (g_pInput->m_Y > start_y + MINIMUM_SWIPE && g_pInput->m_X < start_x + SWIPE_OFFSET && g_pInput->m_X > start_x - SWIPE_OFFSET)
				{
					IwTrace(APP, ("move down"));
				}
				g_pInput->Reset();
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
