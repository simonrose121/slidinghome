#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "main.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "pauseMenu.h"
#include "stringExtensions.h"

#include <iostream>
#include <fstream>

#define GRID_OFFSET_X 41
#define GRID_OFFSET_Y 37

Game::~Game()
{
	if (currentState != State::COMPLETE)
		delete grid;
}

void Game::Init()
{
	Scene::Init();

	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;

	CSprite* background = new CSprite();
	background->m_X = IwGxGetScreenWidth() / 2;
	background->m_Y = IwGxGetScreenHeight() / 2;
	background->SetImage(g_pResources->getGameBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
	AddChild(background);

	//TODO: only initialise this if onScreenButtons bool is set

	isMoving = false;
	minimumSwipe = 100 * graphicsScale;
	swipeOffset = 200 * graphicsScale;
	pressedDown = false;
}

void Game::Update(float deltaTime, float alphaMul) 
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
			if (pauseButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				pauseMenu();
				currentState = State::PAUSED;
			}
		}

		// If input is in grid
		if (g_pInput->m_Y >= grid->getGridOriginY())
		{
			if (g_pInput->m_Touched && !g_pInput->m_PrevTouched)
			{
				if (!pressedDown)
				{
					//record start position of movement
					start_x = g_pInput->m_X;
					start_y = g_pInput->m_Y;
					pressedDown = true;

					IwTrace(APP, ("pressed down is %d", pressedDown));
				}

				IwTrace(APP, ("currently pressing down"));

				IwTrace(APP, ("start x,y = %d,%d current x,y = %d,%d", start_x, start_y, g_pInput->m_X, g_pInput->m_Y));
			}
			else if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				// Check current input is smaller than start touch position minus min swipe
				if (g_pInput->m_X < start_x - minimumSwipe && g_pInput->m_Y < start_y + swipeOffset && g_pInput->m_Y > start_y - swipeOffset)
				{
					IwTrace(APP, ("move left"));
					if (!isMoving)
						grid->MovePlayerLeft();
				}
				if (g_pInput->m_Y < start_y - minimumSwipe && g_pInput->m_X < start_x + swipeOffset && g_pInput->m_X > start_x - swipeOffset)
				{
					IwTrace(APP, ("move up"));
					if (!isMoving)
						grid->MovePlayerUp();
				}
				if (g_pInput->m_X > start_x + minimumSwipe && g_pInput->m_Y < start_y + swipeOffset && g_pInput->m_Y > start_y - swipeOffset)
				{
					IwTrace(APP, ("move right"));
					if (!isMoving)
						grid->MovePlayerRight();
				}
				if (g_pInput->m_Y > start_y + minimumSwipe && g_pInput->m_X < start_x + swipeOffset && g_pInput->m_X > start_x - swipeOffset)
				{
					IwTrace(APP, ("move down"));
					if (!isMoving)
						grid->MovePlayerDown();
				}
				pressedDown = false;
				g_pInput->Reset();
			}
		}
	}
}

void Game::Render()
{
	Scene::Render();
}

void Game::pauseMenu() 
{
	PauseMenu* pausemenu = (PauseMenu*)g_pSceneManager->Find("pausemenu");
	g_pSceneManager->SwitchTo(pausemenu);
}

void Game::NewGame(int width, int height)
{
	grid = new Grid(this);
	grid->GenerateLevel(1, width, height, (int)(GRID_OFFSET_X * graphicsScale), (int)(GRID_OFFSET_Y * graphicsScale), IwGxGetScreenWidth());

	// Create Start Game button
	float x_pos = (float)IwGxGetScreenWidth() / 1;
	float y_pos = (float)IwGxGetScreenHeight() / 1;
	pauseButton = new CSprite();
	pauseButton->SetImage(g_pResources->getPauseButton());
	pauseButton->m_X = x_pos;
	pauseButton->m_Y = y_pos;
	pauseButton->m_W = pauseButton->GetImage()->GetWidth();
	pauseButton->m_H = pauseButton->GetImage()->GetHeight();
	pauseButton->m_AnchorX = 1;
	pauseButton->m_AnchorY = 1;
	pauseButton->m_ScaleX = getGraphicsScale();
	pauseButton->m_ScaleY = getGraphicsScale();
	AddChild(pauseButton);

	//Create Star file
	std::ifstream file("star1.txt");
	int fileNumber = 0;
	file >> fileNumber;
	x_pos = (float)IwGxGetScreenWidth() / 1.05;
	y_pos = (float)IwGxGetScreenHeight() / 15;
	star = new CSprite();
	if (fileNumber == 1){
		star->SetImage(g_pResources->getStar());
	}
	else {
		star->SetImage(g_pResources->getHoloStar());
	}
	star->m_X = x_pos;
	star->m_Y = y_pos;
	star->m_W = star->GetImage()->GetWidth();
	star->m_H = star->GetImage()->GetHeight();
	star->m_AnchorX = 1;
	star->m_AnchorY = 1;
	star->m_ScaleX = getGraphicsScale();
	star->m_ScaleY = getGraphicsScale();
	AddChild(star);

	currentState = State::INPROGRESS;
}

void Game::EndGame()
{
	isMoving = false;
	//cleaup this line
	//grid = new Grid(this);
	delete grid;
	currentState = State::COMPLETE;
}
