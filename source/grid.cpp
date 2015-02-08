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

using namespace IwTween;

Grid::Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width)
{
	int map[11][16] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

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
			switch (map[x][y])
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
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getPlayer());
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
				homeIndex = x + width * y;
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
	
	if (distance > 0)
	{
		float speed = distance / speedVal;
		float new_X = gameObjects[playerIndex]->m_X - (distance * gameObjectSize);

		Game* game = (Game*)g_pSceneManager->Find("game");
		game->getTweener().Tween(speed,
			FLOAT, &player->m_X, new_X,
			EASING, Ease::sineInOut,
			END);

		UpdatePosition(distance, LEFT);
		TestMap(LEFT);
	}
}

void Grid::MovePlayerRight()
{
	int distance = getDistance(RIGHT);

	if (distance > 0)
	{
		float speed = distance / speedVal;
		float new_X = gameObjects[playerIndex]->m_X + (distance * gameObjectSize);

		Game* game = (Game*)g_pSceneManager->Find("game");
		game->getTweener().Tween(speed,
			FLOAT, &player->m_X, new_X,
			EASING, Ease::sineInOut,
			END);

		// Update position in grid
		UpdatePosition(distance, RIGHT);
		TestMap(RIGHT);
	}
}

void Grid::MovePlayerUp()
{
	int distance = getDistance(UP);

	if (distance > 0)
	{
		float speed = distance / speedVal;
		float new_Y = gameObjects[playerIndex]->m_Y - (distance * gameObjectSize);

		Game* game = (Game*)g_pSceneManager->Find("game");
		game->getTweener().Tween(speed,
			FLOAT, &player->m_Y, new_Y,
			EASING, Ease::sineInOut,
			END);

		// Update position in grid
		UpdatePosition(distance, UP);
		TestMap(UP);
	}
}

void Grid::MovePlayerDown()
{
	int distance = getDistance(DOWN);

	if (distance > 0)
	{
		float speed = distance / speedVal;
		float new_Y = gameObjects[playerIndex]->m_Y + (distance * gameObjectSize);

		Game* game = (Game*)g_pSceneManager->Find("game");
		game->getTweener().Tween(speed,
			FLOAT, &player->m_Y, new_Y,
			EASING, Ease::sineInOut,
			END);

		// Update position in grid
		UpdatePosition(distance, DOWN);
		TestMap(DOWN);
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
		IwTrace(APP, ("my index is now %d", playerIndex));
		break;
	case RIGHT:
		gameObjects[playerIndex + distance]->setGridCoords(x + distance, y);
		gameObjects[playerIndex + distance]->setId(2);
		gameObjects[playerIndex]->setId(0);
		playerIndex = playerIndex + distance;
		IwTrace(APP, ("my index is now %d", playerIndex));
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

void Grid::TestMap(Direction dir)
{
	std::pair<int, int> coords = gameObjects[playerIndex]->getCoords();
	int x = coords.first;
	int y = coords.second;

	switch (dir)
	{
	case LEFT:
		if (gameObjects[(x - 1) + width*y]->getId() == 3)
		{
			WinningState();
		}
		break;
	case RIGHT:
		if (gameObjects[(x + 1) + width*y]->getId() == 3)
		{
			WinningState();
		}
		break;
	case UP:
		if (gameObjects[(x + width*y) - width]->getId() == 3)
		{
			WinningState();
		}
		break;
	case DOWN:
		if (gameObjects[(x + width*y) + width]->getId() == 3)
		{
			WinningState();
		}
		break;
	}
}

void Grid::WinningState() 
{
	/*Game* main_menu = (Game*)g_pSceneManager->Find("mainmenu");
	g_pSceneManager->SwitchTo(main_menu);*/
	IwTrace(APP, ("win"));
}
