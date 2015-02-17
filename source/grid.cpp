#include "IwGx.h"
#include "IwTween.h"
#include "audio.h"
#include "scene.h"
#include "grid.h"
#include "game.h"
#include "blankObject.h"
#include "resources.h"
#include "main.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

#define SIZEY 15
#define SIZEX 11

using namespace std;
using namespace IwTween;

Grid::Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width)
{
	ifstream file("maps/level1.txt");
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
	gameObjects = new GameObject* [num_columns * num_rows];

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
				gameObjects[x + width*y]->setId(0);
				break;

			case 1:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getRock());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				gameObjects[x + width*y]->setId(1);
				break;

			case 2:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getPlayerDownAtlas());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				gameObjects[x + width*y]->setId(2);
				player = gameObjects[x + width*y];
				playerIndex = x + width * y;
				break;
			case 3:
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getHome());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				gameObjects[x + width*y]->setId(3);
			}
			scene->AddChild(gameObjects[x + width*y]);
		}
	}

	PrintGrid();
}

Grid::~Grid()
{
	if (gameObjects != 0)
		delete[] gameObjects;
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
		gameObjects[playerIndex - distance]->setGridCoords(x - distance, y);
		gameObjects[playerIndex - distance]->setId(2);
		gameObjects[playerIndex]->setId(0);
		playerIndex = playerIndex - distance;
		break;
	case RIGHT:
		gameObjects[playerIndex + distance]->setGridCoords(x + distance, y);
		gameObjects[playerIndex + distance]->setId(2);
		gameObjects[playerIndex]->setId(0);
		playerIndex = playerIndex + distance;
		break;
	case UP:
		gameObjects[playerIndex - (distance * width)]->setGridCoords(x, y - distance);
		gameObjects[playerIndex - (distance * width)]->setId(2);
		gameObjects[playerIndex]->setId(0);
		playerIndex = playerIndex - (distance * width);
		break;
	case DOWN:
		gameObjects[playerIndex + (distance * width)]->setGridCoords(x, y + distance);
		gameObjects[playerIndex + (distance * width)]->setId(2);
		gameObjects[playerIndex]->setId(0);
		playerIndex = playerIndex + (distance * width);
		break;
	}

	PrintGrid();
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
		while (gameObjects[(x - (distance + 1)) + width*y]->getId() == 0)
		{
			distance++;
		}
		break;
	case RIGHT:
		while (gameObjects[(x + (distance + 1)) + width*y]->getId() == 0)
		{
			distance++;
		}
		break;
	case UP:
		while (gameObjects[(x + width*y) - (width*(distance + 1))]->getId() == 0)
		{
			distance++;
		}
		break;
	case DOWN:
		while (gameObjects[(x + width*y) + (width*(distance + 1))]->getId() == 0)
		{
			distance++;
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
	Game* main_menu = (Game*)g_pSceneManager->Find("endscreen");
	g_pSceneManager->SwitchTo(main_menu);
	IwTrace(APP, ("win"));
}

void Grid::SetComplete(CTween* pTween)
{
	Game* game = (Game*)g_pSceneManager->Find("game");
	game->setIsMoving(false);
}

bool Grid::TestMap(Direction dir)
{
	std::pair<int, int> coords = gameObjects[playerIndex]->getCoords();
	int x = coords.first;
	int y = coords.second;

	switch (dir)
	{
	case LEFT:
		if (gameObjects[(x - 1) + width*y]->getId() == 3)
		{
			return true;
		}
		break;
	case RIGHT:
		if (gameObjects[(x + 1) + width*y]->getId() == 3)
		{
			return true;
		}
		break;
	case UP:
		if (gameObjects[(x + width*y) - width]->getId() == 3)
		{
			return true;
		}
		break;
	case DOWN:
		if (gameObjects[(x + width*y) + width]->getId() == 3)
		{
			return true;
		}
		break;
	}
	return false;
}
