#include "IwGx.h"
#include "IwTween.h"
#include "audio.h"
#include "scene.h"
#include "grid.h"
#include "game.h"
#include "resources.h"
#include "main.h"
#include "endScreen.h"
#include "vibration.h"

#include <iostream>
#include <fstream>
#include <string>

#define SIZEY 15
#define SIZEX 11

using namespace std;
using namespace IwTween;

Grid::Grid(CNode* scene)
{
	game = scene;
}

Grid::~Grid()
{
	if (gameObjects != 0)
	{
		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < height; x++)
			{
				game->RemoveChild(gameObjects[x * width + y]);
				//cleanup this line 
				//gameObjects[x + width*y] = new GameObject();
				delete gameObjects[x * width + y];
			}
		}
		//cleanup this line 
		//gameObjects = new GameObject*[num_columns * num_rows];
		delete[] gameObjects;
	}
}

void Grid::GenerateLevel(std::string levelNo, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width)
{
	std::string filename = "maps/level" + levelNo;
	filename += ".txt";
	ifstream file(filename.c_str());
	int map[SIZEY][SIZEX];
	for (int y = 0; y < num_rows; y++)
	{
		for (int x = 0; x < num_columns; x++)
		{
			if (!(file >> map[y][x]))
			{
				break;
			}
		}
		if (!file) break;
	}
	width = num_columns;
	height = num_rows;
	gameObjects = new GameObject*[num_columns * num_rows];

	int bm_width = (int)g_pResources->getRock()->GetWidth();
	gameObjectSize = (IwGxGetScreenWidth() * bm_width) / GRAPHIC_DESIGN_WIDTH;
	speedVal = 8.0;

	float gem_scale = (float)gameObjectSize / bm_width;

	gridOriginX = offset_x;
	gridOriginY = IwGxGetScreenHeight() - (num_rows * gameObjectSize) - offset_y;

	for (int y = 0; y < num_rows; y++)
	{
		for (int x = 0; x < num_columns; x++)
		{
			gameObjects[x + width*y] = new GameObject();
			gameObjects[x + width*y]->setGridCoords(x, y);
			switch (map[y][x])
			{
			case 0:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getBlank());
				gameObjects[x + width*y]->setId(BLANK);
				break;

			case 1:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getRock());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				gameObjects[x + width*y]->setId(ROCK);
				break;

			case 2:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getPlayerDownAtlas());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				gameObjects[x + width*y]->setId(PLAYER);
				player = gameObjects[x + width*y];
				playerIndex = x + width * y;
				break;

			case 3:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getHome());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				gameObjects[x + width*y]->setId(HOME);
				break;

			case 4:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getSnowpatch());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				gameObjects[x + width*y]->setId(SNOWPATCH);
				break;

			}
			game->AddChild(gameObjects[x + width*y]);
		}
	}

	// Initialise on screen buttons
	Game* game = (Game*)g_pSceneManager->Find("game");
	game->InitOnScreenButtons();

	onSnowPatch = false;

	PrintGrid();
}

void Grid::MovePlayerLeft()
{
	int distance = getDistance(LEFT);

	float new_X = gameObjects[playerIndex]->m_X - (distance * gameObjectSize);
		
	MovePlayer(LEFT, new_X, distance);

	player->SetAtlas(g_pResources->getPlayerLeftAtlas());
	player->SetAnimRepeat(distance/2);
}

void Grid::MovePlayerRight()
{
	int distance = getDistance(RIGHT);

	float new_X = gameObjects[playerIndex]->m_X + (distance * gameObjectSize);

	MovePlayer(RIGHT, new_X, distance);

	player->SetAtlas(g_pResources->getPlayerRightAtlas());
	player->SetAnimRepeat(distance / 2);
}

void Grid::MovePlayerUp()
{
	int distance = getDistance(UP);

	float new_Y = gameObjects[playerIndex]->m_Y - (distance * gameObjectSize);

	MovePlayer(UP, new_Y, distance);

	player->SetAtlas(g_pResources->getPlayerUpAtlas());
	player->SetAnimRepeat(distance / 2);
}

void Grid::MovePlayerDown()
{
	int distance = getDistance(DOWN);

	float new_Y = gameObjects[playerIndex]->m_Y + (distance * gameObjectSize);

	MovePlayer(DOWN, new_Y, distance);
		
	player->SetAtlas(g_pResources->getPlayerDownAtlas());
	player->SetAnimRepeat(distance / 2);
}

void Grid::MovePlayer(Direction dir, float newPos, int distance)
{
	float speed = distance / speedVal;

	UpdatePosition(distance, dir);
	bool hasWon = TestMap(dir);

	Game* game = (Game*)g_pSceneManager->Find("game");
	if (dir == DOWN || dir == UP)
	{
		if (hasWon) {
			game->getTweener().Tween(speed,
				FLOAT, &player->m_Y, newPos,
				EASING, Ease::sineInOut,
				ONCOMPLETE, WinningState,
				END);
			game->setIsMoving(true);
		}
		else {
			game->getTweener().Tween(speed,
				FLOAT, &player->m_Y, newPos,
				EASING, Ease::sineInOut,
				ONCOMPLETE, SetComplete,
				END);
			game->setIsMoving(true);
		}
	}
	if (dir == LEFT || dir == RIGHT)
	{
		if (hasWon) {
			game->getTweener().Tween(speed,
				FLOAT, &player->m_X, newPos,
				EASING, Ease::sineInOut,
				ONCOMPLETE, WinningState,
				END);
			game->setIsMoving(true);
		}
		else {
			game->getTweener().Tween(speed,
				FLOAT, &player->m_X, newPos,
				EASING, Ease::sineInOut,
				ONCOMPLETE, SetComplete,
				END);
			game->setIsMoving(true);
		}
	}
}

void Grid::UpdatePosition(int distance, Direction dir)
{
	std::pair<int, int> coords = gameObjects[playerIndex]->getCoords();
	int x = coords.first;
	int y = coords.second;

	switch (dir)
	{
	case LEFT:
		CheckIfOnSnowpatch();
		//if the destination will be a snowpatch then set bool
		if (gameObjects[playerIndex - distance]->getId() == SNOWPATCH)
		{
			onSnowPatch = true;
		}
		gameObjects[playerIndex - distance]->setGridCoords(x - distance, y);
		gameObjects[playerIndex - distance]->setId(PLAYER);
		playerIndex = playerIndex - distance;
		break;
	case RIGHT:
		CheckIfOnSnowpatch();
		if (gameObjects[playerIndex - distance]->getId() == SNOWPATCH)
		{
			onSnowPatch = true;
		}
		gameObjects[playerIndex + distance]->setGridCoords(x + distance, y);
		gameObjects[playerIndex + distance]->setId(PLAYER);
		playerIndex = playerIndex + distance;
		break;
	case UP:
		CheckIfOnSnowpatch();
		if (gameObjects[playerIndex - (distance * width)]->getId() == SNOWPATCH)
		{
			onSnowPatch = true;
		}
		gameObjects[playerIndex - (distance * width)]->setGridCoords(x, y - distance);
		gameObjects[playerIndex - (distance * width)]->setId(PLAYER);
		playerIndex = playerIndex - (distance * width);
		break;
	case DOWN:
		CheckIfOnSnowpatch();
		if (gameObjects[playerIndex + (distance * width)]->getId() == SNOWPATCH)
		{
			onSnowPatch = true;
		}
		gameObjects[playerIndex + (distance * width)]->setGridCoords(x, y + distance);
		gameObjects[playerIndex + (distance * width)]->setId(PLAYER);
		playerIndex = playerIndex + (distance * width);
		break;
	}

	PrintGrid();
}

void Grid::CheckIfOnSnowpatch() 
{
	// check if player is on snowpatch set that position back to a snowpatch when he moves off
	if (onSnowPatch)
	{
		gameObjects[playerIndex]->setId(SNOWPATCH);
		onSnowPatch = false;
	}
	else
	{
		gameObjects[playerIndex]->setId(BLANK);
	}
}

int Grid::getIndex()
{
	int index = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (gameObjects[x + width * y]->getId() == 2)
			{
				index = x + width * y;
			}
		}
	}

	IwTrace(APP, ("player found at %d", index));

	return index;
}

int Grid::getDistance(Direction dir)
{
	int distance = 0;

	std::pair<int, int> coords = gameObjects[playerIndex]->getCoords();
	int x = coords.first;
	int y = coords.second;

	IwTrace(APP, ("i am at %d, %d", x, y));

	switch (dir)
	{
	case LEFT:
		while (gameObjects[(x - (distance + 1)) + width*y]->getId() == BLANK)
		{
			distance++;
			// Check for snowpatch
			if (gameObjects[(x - (distance + 1)) + width*y]->getId() == SNOWPATCH)
			{
				// Ensure player is on snowpatch
				distance++;
				break;
			}
		}
		break;
	case RIGHT:
		while (gameObjects[(x + (distance + 1)) + width*y]->getId() == BLANK)
		{
			distance++;
			if (gameObjects[(x + (distance + 1)) + width*y]->getId() == SNOWPATCH)
			{
				distance++;
				break;
			}
		}
		break;
	case UP:
		while (gameObjects[(x + width*y) - (width*(distance + 1))]->getId() == BLANK)
		{
			distance++;
			if (gameObjects[(x + width*y) - (width*(distance + 1))]->getId() == SNOWPATCH)
			{
				distance++;
				break;
			}
		}
		break;
	case DOWN:
		while (gameObjects[(x + width*y) + (width*(distance + 1))]->getId() == BLANK)
		{
			distance++;
			if (gameObjects[(x + width*y) + (width*(distance + 1))]->getId() == SNOWPATCH)
			{
				distance++;
				break;
			}
		}
		break;
	}

	IwTrace(APP, ("distance is %d", distance));

	return distance;
}

void Grid::PrintGrid()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			std::cout << gameObjects[x + width * y]->getId();
		}
		std::cout << "\n";
	}
}

void Grid::WinningState(CTween* pTween)
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	std::string filename = "star" + game->getLevelNum();
	filename += ".txt";
	std::ofstream file(filename.c_str());
	int complete = 1;
	file << complete;
	file.close();

	g_pVibration->Vibrate();

	game->EndGame();

	EndScreen* end_screen = (EndScreen*)g_pSceneManager->Find("endscreen");
	g_pSceneManager->SwitchTo(end_screen);

	IwTrace(APP, ("win"));
}

void Grid::SetComplete(CTween* pTween)
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	game->setIsMoving(false);
	g_pVibration->Vibrate();
}

bool Grid::TestMap(Direction dir)
{
	std::pair<int, int> coords = gameObjects[playerIndex]->getCoords();
	int x = coords.first;
	int y = coords.second;

	switch (dir)
	{
	case LEFT:
		if (gameObjects[(x - 1) + width*y]->getId() == HOME)
		{
			return true;
		}
		break;
	case RIGHT:
		if (gameObjects[(x + 1) + width*y]->getId() == HOME)
		{
			return true;
		}
		break;
	case UP:
		if (gameObjects[(x + width*y) - width]->getId() == HOME)
		{
			return true;
		}
		break;
	case DOWN:
		if (gameObjects[(x + width*y) + width]->getId() == HOME)
		{
			return true;
		}
		break;
	}
	return false;
}
