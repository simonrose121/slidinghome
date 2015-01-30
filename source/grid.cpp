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
	int map[11][17] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	width = num_columns;
	height = num_rows;
	gameObjects = new GameObject* [num_columns * (num_rows + 1)];

	int bm_width = (int)g_pResources->getRock()->GetWidth();
	gameObjectSize = (IwGxGetScreenWidth() * bm_width) / GRAPHIC_DESIGN_WIDTH;

	float gem_scale = (float)gameObjectSize / bm_width;

	gridOriginX = offset_x;
	gridOriginY = IwGxGetScreenHeight() - (num_rows * gameObjectSize) - offset_y;

	for (int y = 0; y < num_rows; y++)
	{
		for (int x = 0; x < num_columns; x++)
		{
			switch (map[x][y])
			{
			case 0:
				gameObjects[x + width*y] = new BlankObject();
				gameObjects[x + width*y]->setId(0);
				gameObjects[x + width*y]->setGridCoords(x, y);
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getBlank());
				scene->AddChild(gameObjects[x + width*y]);
				break;

			case 1:
				gameObjects[x + width*y] = new Rock();
				gameObjects[x + width*y]->setId(1);
				gameObjects[x + width*y]->setGridCoords(x, y);
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getRock());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				scene->AddChild(gameObjects[x + width*y]);
				break;

			case 2:
				IwTrace(APP, ("GameObject[%d], Id(%d)", x + width*y, 2));
				gameObjects[x + width*y] = new Player();
				gameObjects[x + width*y]->setId(2);
				gameObjects[x + width*y]->setGridCoords(x, y);
				gameObjects[x + width*y]->Init((float)x * gameObjectSize + gridOriginX, gridOriginY + (float)y * gameObjectSize, g_pResources->getPlayer());
				gameObjects[x + width*y]->m_ScaleX = gem_scale;
				gameObjects[x + width*y]->m_ScaleY = gem_scale;
				scene->AddChild(gameObjects[x + width*y]);
				break;
			}
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
	int index = getIndex();
	Player* player = (Player*)gameObjects[index];
	int distance = getDistance(LEFT, index);
	float new_X = player->m_X - (distance * gameObjectSize);

	IwTrace(APP, ("new x = %f", new_X));

	// Game objects is never pointing in the correct array position
	Game* game = (Game*)g_pSceneManager->Find("game");
	game->getTweener().Tween(0.5f,
		FLOAT, &player->m_X, new_X,
		EASING, Ease::sineInOut,
		END);

	UpdatePosition(index, distance, LEFT);
}

void Grid::MovePlayerRight()
{
	int index = getIndex();

	Player* player = (Player*)gameObjects[index];
	int distance = getDistance(RIGHT, index);
	float new_X = player->m_X + (distance * gameObjectSize);

	IwTrace(APP, ("new x = %f", new_X));

	// Tween player to new position

	// For some reason game objects[index] is a rock at this point on the second tween?
	Game* game = (Game*)g_pSceneManager->Find("game");
	game->getTweener().Tween(0.5f,
		FLOAT, &player->m_X, new_X,
		EASING, Ease::sineInOut,
		END);

	// Update position in grid
	UpdatePosition(index, distance, RIGHT);
}

void Grid::MovePlayerUp()
{
}

void Grid::MovePlayerDown()
{
}

void Grid::UpdatePosition(int index, int distance, Grid::Direction dir)
{
	Player* player = (Player*)gameObjects[index];

	std::pair<int, int> coords = player->getCoords();
	int x = coords.first;
	int y = coords.second;

	IwTrace(APP, ("2 is at %d,%d", x, y));
	IwTrace(APP, ("player is at index %d", index));

	switch (dir)
	{
	case LEFT:
		player->setGridCoords(x - distance, y);
		gameObjects[index - distance]->setId(2);
		IwTrace(APP, ("index is %d", index - distance));

		break;
	case RIGHT:
		player->setGridCoords(x + distance, y);
		gameObjects[index + distance]->setId(2);
		IwTrace(APP, ("index is %d", index + distance));

		break;
	case UP:
		//gameObjects[index]->setGridCoords(x, y + distance);
		//gameObjects[index + distance]->setId(2);
		break;
	case DOWN:
		//gameObjects[index]->setGridCoords(x, y - distance);
		//gameObjects[index + distance]->setId(2);
		break;
	}

	player->setId(0);

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

	IwTrace(APP, ("player is at %d", index));

	return index;
}

int Grid::getDistance(Grid::Direction dir, int index)
{
	std::pair<int, int> coords = gameObjects[index]->getCoords();
	int x = coords.first;
	int y = coords.second;

	int distance = 0;

	int initialIndex = (x - (distance + 1)) + width*y;


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
		while (gameObjects[(x + (width*y - (distance + 1)))]->getId() == 0)
		{
			distance++;
		}
		break;
	case DOWN:
		while (gameObjects[(x + (width*y - (distance - 1)))]->getId() == 0)
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
