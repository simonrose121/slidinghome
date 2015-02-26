#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "main.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "pauseMenu.h"
#include "stringExtensions.h"
#include "s3eVibra.h"

#include <iostream>
#include <fstream>

#define GRID_OFFSET_X 41
#define GRID_OFFSET_Y 37

Game::~Game()
{
	if (currentState != COMPLETE)
		delete grid;
}

void Game::Init()
{
	Scene::Init();

	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;
	buttonScale = 2;

	background = new CSprite();
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

	isMoving = false;
	minimumSwipe = 100 * graphicsScale;
	swipeOffset = 200 * graphicsScale;
	pressedDown = false;
}

void Game::ChangeBackground(){
	if (changeToHighContrast){
		background->SetImage(g_pResources->getGameBGHC());
	}
	else{
		background->SetImage(g_pResources->getGameBG());
	}
}

void Game::InitOnScreenButtons()
{
	if (showOnScreenButtons) 
	{
		upButton = new CSprite();
		upButton->m_X = IwGxGetScreenWidth() / 2;
		upButton->m_Y = IwGxGetScreenHeight() / 4;
		upButton->SetImage(g_pResources->getUpButton());
		upButton->m_W = upButton->GetImage()->GetWidth();
		upButton->m_H = upButton->GetImage()->GetHeight();
		upButton->m_AnchorX = 1;
		upButton->m_AnchorY = 1;
		upButton->m_ScaleX = graphicsScale * buttonScale;
		upButton->m_ScaleY = graphicsScale * buttonScale;
		AddChild(upButton);

		rightButton = new CSprite();
		rightButton->m_X = IwGxGetScreenWidth() / 1.3;
		rightButton->m_Y = IwGxGetScreenHeight() / 2.6;
		rightButton->SetImage(g_pResources->getRightButton());
		rightButton->m_W = rightButton->GetImage()->GetWidth();
		rightButton->m_H = rightButton->GetImage()->GetHeight();
		rightButton->m_AnchorX = 1;
		rightButton->m_AnchorY = 1;
		rightButton->m_ScaleX = graphicsScale * buttonScale;
		rightButton->m_ScaleY = graphicsScale * buttonScale;
		AddChild(rightButton);

		downButton = new CSprite();
		downButton->m_X = IwGxGetScreenWidth() / 2;
		downButton->m_Y = IwGxGetScreenHeight() / 1.8;
		downButton->SetImage(g_pResources->getDownButton());
		downButton->m_W = downButton->GetImage()->GetWidth();
		downButton->m_H = downButton->GetImage()->GetHeight();
		downButton->m_AnchorX = 1;
		downButton->m_AnchorY = 1;
		downButton->m_ScaleX = graphicsScale * buttonScale;
		downButton->m_ScaleY = graphicsScale * buttonScale;
		AddChild(downButton);

		leftButton = new CSprite();
		leftButton->m_X = IwGxGetScreenWidth() / 3.3;
		leftButton->m_Y = IwGxGetScreenHeight() / 2.6;
		leftButton->SetImage(g_pResources->getLeftButton());
		leftButton->m_W = leftButton->GetImage()->GetWidth();
		leftButton->m_H = leftButton->GetImage()->GetHeight();
		leftButton->m_AnchorX = 1;
		leftButton->m_AnchorY = 1;
		leftButton->m_ScaleX = graphicsScale * buttonScale;
		leftButton->m_ScaleY = graphicsScale * buttonScale;
		AddChild(leftButton);
	}
}

void Game::CleanupOnScreenButtons()
{
	if (showOnScreenButtons) 
	{
		// Remove children from scene
		RemoveChild(upButton);
		RemoveChild(rightButton);
		RemoveChild(downButton);
		RemoveChild(leftButton);

		// Cleanup buttons so they can be reinitialised
		delete rightButton;
		delete downButton;
		delete upButton;
		delete leftButton;
	}
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
				MoveToPauseMenu();
				currentState = PAUSED;

			}

			if (showOnScreenButtons)
			{
				if (upButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					IwTrace(APP, ("move up button"));
					if (!isMoving)
						grid->MovePlayerUp();
				}
				else if (rightButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					IwTrace(APP, ("move right button"));
					if (!isMoving)
						grid->MovePlayerRight();
				}
				else if (downButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					IwTrace(APP, ("move down button"));
					if (!isMoving)
						grid->MovePlayerDown();
				}
				else if (leftButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					IwTrace(APP, ("move left button"));
					if (!isMoving)
						grid->MovePlayerLeft();
				}
				g_pInput->Reset();
			}
		}

		// If input is in grid
		if (g_pInput->m_Y >= grid->getGridOriginY())
		{
			if (!showOnScreenButtons)
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
}

void Game::Render()
{
	Scene::Render();
}

void Game::MoveToPauseMenu()
{
	PauseMenu* pausemenu = (PauseMenu*)g_pSceneManager->Find("pausemenu");
	g_pSceneManager->SwitchTo(pausemenu);
}

void Game::NewGame(int width, int height)
{
	grid = new Grid(this);
	grid->GenerateLevel(1, width, height, (int)(GRID_OFFSET_X * graphicsScale), (int)(GRID_OFFSET_Y * graphicsScale), IwGxGetScreenWidth());

	// Create Pause Button
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
	file.close();
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

	currentState = INPROGRESS;
}

void Game::EndGame()
{
	isMoving = false;
	CleanupOnScreenButtons();
	//cleaup this line
	//grid = new Grid(this);
	delete grid;
	currentState = COMPLETE;
}
