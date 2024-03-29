#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "main.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "pauseMenu.h"
#include "s3eVibra.h"
#include "sound.h"
#include "levelSelect.h"

#include <sstream>
#include <iostream>
#include <fstream>

Game::~Game()
{
	if (currentState != COMPLETE)
		delete grid;
}

void Game::Init()
{
	Scene::Init();

	// set graphics scale for all assets
	graphicsScale = (float)IwGxGetScreenWidth() / GRAPHIC_DESIGN_WIDTH;

	// initialise background
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

	// set initial boolean values
	isMoving = false;
	minimumSwipe = 100 * graphicsScale;
	swipeOffset = 200 * graphicsScale;
	pressedDown = false;
	instructionsOn = false;
}

void Game::ChangeBackground()
{
	if (changeToHighContrast)
	{
		background->SetImage(g_pResources->getGameBGHC());
	}
	else
	{
		background->SetImage(g_pResources->getGameBG());
	}
}

void Game::InitOnScreenButtons()
{
	if (showOnScreenButtons) 
	{
		upButton = new CSprite();
		upButton->m_X = IwGxGetScreenWidth() / 2;
		upButton->m_Y = IwGxGetScreenHeight() / 5.36;
		upButton->SetImage(g_pResources->getUpButton());
		upButton->m_W = upButton->GetImage()->GetWidth();
		upButton->m_H = upButton->GetImage()->GetHeight();
		upButton->m_AnchorX = 0.5;
		upButton->m_AnchorY = 0.5;
		upButton->m_ScaleX = graphicsScale;
		upButton->m_ScaleY = graphicsScale;
		AddChild(upButton);

		rightButton = new CSprite();
		rightButton->SetImage(g_pResources->getRightButton());
		rightButton->m_X = IwGxGetScreenWidth() - (rightButton->GetImage()->GetWidth() * graphicsScale) / 2;
		rightButton->m_Y = IwGxGetScreenHeight() / 2;
		rightButton->m_W = rightButton->GetImage()->GetWidth();
		rightButton->m_H = rightButton->GetImage()->GetHeight();
		rightButton->m_AnchorX = 0.5;
		rightButton->m_AnchorY = 0.5;
		rightButton->m_ScaleX = graphicsScale;
		rightButton->m_ScaleY = graphicsScale;
		AddChild(rightButton);

		downButton = new CSprite();
		downButton->m_X = IwGxGetScreenWidth() / 2;
		downButton->m_Y = IwGxGetScreenHeight() / 1.23;
		downButton->SetImage(g_pResources->getDownButton());
		downButton->m_W = downButton->GetImage()->GetWidth();
		downButton->m_H = downButton->GetImage()->GetHeight();
		downButton->m_AnchorX = 0.5;
		downButton->m_AnchorY = 0.5;
		downButton->m_ScaleX = graphicsScale;
		downButton->m_ScaleY = graphicsScale;
		AddChild(downButton);

		leftButton = new CSprite();
		leftButton->SetImage(g_pResources->getLeftButton());
		leftButton->m_X = (leftButton->GetImage()->GetWidth() * graphicsScale) / 2;
		leftButton->m_Y = IwGxGetScreenHeight() / 2;
		leftButton->m_W = leftButton->GetImage()->GetWidth();
		leftButton->m_H = leftButton->GetImage()->GetHeight();
		leftButton->m_AnchorX = 0.5;
		leftButton->m_AnchorY = 0.5;
		leftButton->m_ScaleX = graphicsScale;
		leftButton->m_ScaleY = graphicsScale;
		AddChild(leftButton);
	}
}

void Game::InitLevelCompletePopup()
{
	// set that game is in complete stage
	currentState = COMPLETE;

	// show panel
	levelComplete = new CSprite();
	levelComplete->SetImage(g_pResources->getPopup());
	levelComplete->m_X = (float)IwGxGetScreenWidth() / 2;
	levelComplete->m_Y = (float)IwGxGetScreenHeight() / 2;
	levelComplete->m_W = levelComplete->GetImage()->GetWidth();
	levelComplete->m_H = levelComplete->GetImage()->GetHeight();
	levelComplete->m_AnchorX = 0.5;
	levelComplete->m_AnchorY = 0.5;
	levelComplete->m_ScaleX = getGraphicsScale();
	levelComplete->m_ScaleY = getGraphicsScale();
	AddChild(levelComplete);

	if (levelNum != "12")
	{
		nextText = new CSprite();
		nextText->SetImage(g_pResources->getNextText());
		nextText->m_X = (float)IwGxGetScreenWidth() / 1.6;
		nextText->m_Y = (float)IwGxGetScreenHeight() / 1.6;
		nextText->m_W = nextText->GetImage()->GetWidth();
		nextText->m_H = nextText->GetImage()->GetHeight();
		nextText->m_AnchorX = 0.5;
		nextText->m_AnchorY = 0.5;
		nextText->m_ScaleX = getGraphicsScale();
		nextText->m_ScaleY = getGraphicsScale();
		AddChild(nextText);
	}

	allText = new CSprite();
	allText->SetImage(g_pResources->getAllText());
	allText->m_X = (float)IwGxGetScreenWidth() / 2.6;
	allText->m_Y = (float)IwGxGetScreenHeight() / 1.6;
	allText->m_W = allText->GetImage()->GetWidth();
	allText->m_H = allText->GetImage()->GetHeight();
	allText->m_AnchorX = 0.5;
	allText->m_AnchorY = 0.5;
	allText->m_ScaleX = getGraphicsScale();
	allText->m_ScaleY = getGraphicsScale();
	AddChild(allText);
}

void Game::InitInstructions()
{
	if (!instructionsOn)
	{
		instructionsOn = true;
		instructions = new CSprite();
		instructions->m_X = IwGxGetScreenWidth() / 2;
		instructions->m_Y = IwGxGetScreenHeight() / 2;
		instructions->SetImage(g_pResources->getInstructions());
		instructions->m_W = instructions->GetImage()->GetWidth();
		instructions->m_H = instructions->GetImage()->GetHeight();
		instructions->m_AnchorX = 0.5;
		instructions->m_AnchorY = 0.5;
		instructions->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
		instructions->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
		AddChild(instructions);
	}
}

void Game::CleanupOnScreenButtons()
{
	if (showOnScreenButtons) 
	{
		// remove children from scene
		RemoveChild(upButton);
		RemoveChild(rightButton);
		RemoveChild(downButton);
		RemoveChild(leftButton);

		// cleanup buttons so they can be reinitialised
		delete rightButton;
		delete downButton;
		delete upButton;
		delete leftButton;
	}
}

void Game::CleanLevelCompletePopup()
{
	// delete level popup
	this->RemoveChild(levelComplete);
	this->RemoveChild(allText);
	delete levelComplete;
	delete allText;

	// if its not the last level
	if (levelNum != "12")
	{
		// remove text
		this->RemoveChild(nextText);
		delete nextText;
	}

	// clean up info sign if there
	if (levelNum == "1") 
	{
		if (instructionsOn)
		{
			CleanupInstructions();
		}
	}
}

void Game::CleanupInstructions()
{
	// delete instructions
	this->RemoveChild(instructions);
	delete instructions;
	instructionsOn = false;
}

void Game::Update(float deltaTime, float alphaMul) 
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

	// detect screen tap
	if (m_IsInputActive && m_Manager->getCurrent() == this)
	{
		// check if user has pressed and lifted off
		if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			// these can't be pressed if game is complete
			if (currentState != COMPLETE)
			{
				if (pauseButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					currentState = PAUSED;
					MoveToPauseMenu();
					g_pInput->Reset();
				}

				if (resetButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					if (hasMoved)
					{
						EndGame();
						g_pInput->Reset();
						NewGame(levelNum, 12, 14);
						g_pInput->Reset();
					}
				}
			}

			// level info only active on level 1
			if (levelNum == "1")
			{
				if (levelInfo->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					InitInstructions();
				}
				if (instructionsOn)
				{
					if (instructions->HitTest(g_pInput->m_X, g_pInput->m_Y))
					{
						CleanupInstructions();
						g_pInput->Reset();
					}
				}
			}

			// these can only be pressed if level is complete
			if (currentState == COMPLETE)
			{
				if (allText->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					// end the game
					EndGame();
					CleanLevelCompletePopup();

					// move to level select
					LevelSelect* level_select = (LevelSelect*)g_pSceneManager->Find("levelselect");
					// update completed level stars
					level_select->LevelStars();
					g_pSceneManager->SwitchTo(level_select);
				}
				else 
				{
					if (levelNum != "12")
					{
						if (nextText->HitTest(g_pInput->m_X, g_pInput->m_Y))
						{
							EndGame();
							CleanLevelCompletePopup();

							// convert string to int
							int lNum = atoi(levelNum.c_str());

							// increment 
							lNum++;

							// convert back
							std::ostringstream convert;
							convert << lNum;
							levelNum = convert.str();

							// start new game for that level
							NewGame(levelNum, 12, 14);
						}
					}
				}
			}

			// if on screen buttons active
			if (showOnScreenButtons)
			{
				if (upButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					if (!isMoving)
					{
						hasMoved = true;
						grid->MovePlayerUp();
						g_pSound->SoundFunc();
					}
				}
				else if (rightButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					if (!isMoving)
					{
						hasMoved = true;
						grid->MovePlayerRight();
						g_pSound->SoundFunc();
					}
				}
				else if (downButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					if (!isMoving)
					{
						hasMoved = true;
						grid->MovePlayerDown();
						g_pSound->SoundFunc();
					}
				}
				else if (leftButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					if (!isMoving)
					{
						hasMoved = true;
						grid->MovePlayerLeft();
						g_pSound->SoundFunc();
					}
				}
				g_pInput->Reset();
			}
		}

		// swipe movement
		if (g_pInput->m_Y >= grid->getGridOriginY())
		{
			if (!showOnScreenButtons)
			{
				// when user first presses down
				if (g_pInput->m_Touched && !g_pInput->m_PrevTouched)
				{
					if (!pressedDown)
					{
						//record start position of movement
						start_x = g_pInput->m_X;
						start_y = g_pInput->m_Y;
						pressedDown = true;
					}
				}
				// when user lifts off
				else if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
				{
					// Check current input is smaller than start touch position minus min swipe
					if (g_pInput->m_X < start_x - minimumSwipe && g_pInput->m_Y < start_y + swipeOffset && g_pInput->m_Y > start_y - swipeOffset)
					{
						if (!isMoving)
						{
							hasMoved = true;
							grid->MovePlayerLeft();
							g_pSound->SoundFunc();
						}
					}
					if (g_pInput->m_Y < start_y - minimumSwipe && g_pInput->m_X < start_x + swipeOffset && g_pInput->m_X > start_x - swipeOffset)
					{
						if (!isMoving)
						{
							hasMoved = true;
							grid->MovePlayerUp();
							g_pSound->SoundFunc();
						}
					}
					if (g_pInput->m_X > start_x + minimumSwipe && g_pInput->m_Y < start_y + swipeOffset && g_pInput->m_Y > start_y - swipeOffset)
					{
						if (!isMoving)
						{
							hasMoved = true;
							grid->MovePlayerRight();
							g_pSound->SoundFunc();
						}
					}
					if (g_pInput->m_Y > start_y + minimumSwipe && g_pInput->m_X < start_x + swipeOffset && g_pInput->m_X > start_x - swipeOffset)
					{
						if (!isMoving)
						{
							hasMoved = true;
							grid->MovePlayerDown();
							g_pSound->SoundFunc();
						}
					}
					pressedDown = false;
					g_pInput->Reset();
				}
			}
		}
	}
}

void Game::UpdateSwitches()
{
	grid->SwitchPressed();
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

void Game::NewGame(std::string levelNo, int width, int height)
{
	// generate a new grid
	grid = new Grid(this);
	grid->GenerateLevel(levelNo, width, height, IwGxGetScreenWidth(), graphicsScale);

	float x_pos = (float)IwGxGetScreenWidth() / 8;
	float y_pos = (float)IwGxGetScreenHeight() / 15;
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

	resetButton = new CSprite();
	resetButton->SetImage(g_pResources->getResetButton());
	resetButton->m_X = (float)IwGxGetScreenWidth() / 4;
	resetButton->m_Y = (float)IwGxGetScreenHeight() / 15;
	resetButton->m_W = pauseButton->GetImage()->GetWidth();
	resetButton->m_H = pauseButton->GetImage()->GetHeight();
	resetButton->m_AnchorX = 1;
	resetButton->m_AnchorY = 1;
	resetButton->m_ScaleX = getGraphicsScale();
	resetButton->m_ScaleY = getGraphicsScale();
	AddChild(resetButton);

	// get and set star dependant on if level is previously complete
	levelNum = levelNo;
	std::string filename = "star" + levelNum;
	filename += ".txt";
	std::ifstream file(filename.c_str());
	int fileNumber = 0;
	file >> fileNumber;
	file.close();
	star = new CSprite();
	if (fileNumber == 1)
	{
		star->SetImage(g_pResources->getStar());
	}
	else
	{
		star->SetImage(g_pResources->getHoloStar());
	}
	star->m_X = (float)IwGxGetScreenWidth() / 1.05;;
	star->m_Y = (float)IwGxGetScreenHeight() / 15;
	star->m_W = star->GetImage()->GetWidth();
	star->m_H = star->GetImage()->GetHeight();
	star->m_AnchorX = 1;
	star->m_AnchorY = 1;
	star->m_ScaleX = getGraphicsScale();
	star->m_ScaleY = getGraphicsScale();
	this->AddChild(star);

	// set variables for start a round
	currentState = INPROGRESS;
	hasMoved = false;
	instructionsOn = false; 

	// create level info sign on level 1
	if (levelNum == "1")	{
		levelInfo = new CSprite();
		levelInfo->SetImage(g_pResources->getLevelInfo());
		levelInfo->m_X = (float)IwGxGetScreenWidth() / 1.2;
		levelInfo->m_Y = (float)IwGxGetScreenHeight() / 1.2;
		levelInfo->m_W = levelInfo->GetImage()->GetWidth();
		levelInfo->m_H = levelInfo->GetImage()->GetHeight();
		levelInfo->m_AnchorX = 0.5;
		levelInfo->m_AnchorY = 0.5;
		levelInfo->m_ScaleX = getGraphicsScale();
		levelInfo->m_ScaleY = getGraphicsScale();
		AddChild(levelInfo);
	}
}

void Game::EndGame()
{
	// set the state to complete so the grid isn't attempted to be deleted on close
	currentState = COMPLETE;

	isMoving = false;
	CleanupOnScreenButtons();

	// cleanup grid
	delete grid;

	// clean up star after each level
	this->RemoveChild(star);
	delete star;

	// clean up pause and reset
	this->RemoveChild(pauseButton);
	delete pauseButton;

	this->RemoveChild(resetButton);
	delete resetButton;

	// clean up info sign if there
	if (levelNum == "1")
	{
		this->RemoveChild(levelInfo);
		delete levelInfo;
		if (instructionsOn) 
		{
			this->RemoveChild(instructions);
			delete instructions;
			instructionsOn = false;
		}
	}
}