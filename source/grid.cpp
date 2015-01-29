#include "IwGx.h"
#include "IwTween.h"
#include "audio.h"
#include "scene.h"
#include "grid.h"
#include "game.h"
#include "blankObject.h"
#include "resources.h"
#include "main.h"

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

	Width = num_columns;
	Height = num_rows;
	GameObjects = new GameObject* [num_columns * (num_rows + 1)];

	int bm_width = (int)g_pResources->GetRock()->GetWidth();
	GameObjectSize = (IwGxGetScreenWidth() * bm_width) / GRAPHIC_DESIGN_WIDTH;

	float gem_scale = (float)GameObjectSize / bm_width;

	GridOriginX = offset_x;
	GridOriginY = IwGxGetScreenHeight() - (num_rows * GameObjectSize) - offset_y;

	for (int y = 0; y < num_rows; y++)
	{
		for (int x = 0; x < num_columns; x++)
		{
			switch (map[x][y])
			{
			case 0:
				IwTrace(APP, ("GameObject[%d], Id(%d)", x + Width*y, 0));
				GameObjects[x + Width*y] = new BlankObject();
				GameObjects[x + Width*y]->setId(0);
				GameObjects[x + Width*y]->setGridCoords(x, y);
				GameObjects[x + Width*y]->init((float)x * GameObjectSize + GridOriginX, GridOriginY + (float)y * GameObjectSize, g_pResources->GetBlank());
				scene->AddChild(GameObjects[x + Width*y]);
				break;

			case 1:
				IwTrace(APP, ("GameObject[%d], Id(%d)", x + Width*y, 1));
				GameObjects[x + Width*y] = new Rock();
				GameObjects[x + Width*y]->setId(1);
				GameObjects[x + Width*y]->setGridCoords(x, y);
				GameObjects[x + Width*y]->init((float)x * GameObjectSize + GridOriginX, GridOriginY + (float)y * GameObjectSize, g_pResources->GetRock());
				GameObjects[x + Width*y]->m_ScaleX = gem_scale;
				GameObjects[x + Width*y]->m_ScaleY = gem_scale;
				scene->AddChild(GameObjects[x + Width*y]);
				break;

			case 2:
				IwTrace(APP, ("GameObject[%d], Id(%d)", x + Width*y, 2));
				GameObjects[x + Width*y] = new Player();
				GameObjects[x + Width*y]->setId(2);
				GameObjects[x + Width*y]->setGridCoords(x, y);
				GameObjects[x + Width*y]->init((float)x * GameObjectSize + GridOriginX, GridOriginY + (float)y * GameObjectSize, g_pResources->GetPlayer());
				GameObjects[x + Width*y]->m_ScaleX = gem_scale;
				GameObjects[x + Width*y]->m_ScaleY = gem_scale;
				scene->AddChild(GameObjects[x + Width*y]);
				break;
			}
		}
	}
}

Grid::~Grid()
{
	if (GameObjects != 0)
		delete[] GameObjects;
}

void Grid::movePlayerLeft()
{
	int index = getIndex();

	int distance = getDistance(LEFT, index);

	float new_X = GameObjects[index]->m_X - (distance * GameObjectSize);

	std::pair<int, int> coords = GameObjects[index]->getCoords();
	int x = coords.first;
	int y = coords.second;

	GameObjects[index]->updatePosition(new_X, GameObjects[index]->m_Y);
	GameObjects[index]->setGridCoords(x - distance, y);
	GameObjects[index]->setId(0);
	GameObjects[index - distance]->setId(2);

	Game* game = (Game*)g_pSceneManager->Find("game");

	game->GetTweener().Tween(0.5f,
		FLOAT, &GameObjects[index]->m_X, new_X,
		EASING, Ease::sineInOut,
		END);
}

void Grid::movePlayerRight()
{
	int index = getIndex();

	int distance = getDistance(RIGHT, index);

	float new_X = GameObjects[index]->m_X + (distance * GameObjectSize);

	std::pair<int, int> coords = GameObjects[index]->getCoords();
	int x = coords.first;
	int y = coords.second;

	GameObjects[index]->updatePosition(new_X, GameObjects[index]->m_Y);
	GameObjects[index]->setGridCoords(x + distance, y);
	GameObjects[index]->setId(0);
	GameObjects[index + distance]->setId(2);

	Game* game = (Game*)g_pSceneManager->Find("game");

	game->GetTweener().Tween(0.5f,
		FLOAT, &GameObjects[index]->m_X, new_X,
		EASING, Ease::sineInOut,
		END);
}

void Grid::movePlayerUp()
{
}

void Grid::movePlayerDown()
{
}

int Grid::getIndex()
{
	int index = 0;

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			if (GameObjects[x + Width * y]->getId() == 2)
			{
				index = x + Width * y;
			}
		}
	}

	IwTrace(APP, ("index =  %d", index));

	return index;
}

void Grid::updatePosition(int index, float new_x, int distance)
{
	
}

int Grid::getDistance(Grid::Direction dir, int index)
{
	std::pair<int, int> coords = GameObjects[index]->getCoords();
	int x = coords.first;
	int y = coords.second;

	IwTrace(APP, ("coords [%d][%d]", x, y));

	int distance = 0;

	switch (dir)
	{
	case LEFT:
		while (GameObjects[(x - (distance + 1)) + Width*y]->getId() == 0) 
		{
			distance++;
		}
		break;
	case RIGHT:
		while (GameObjects[(x + (distance + 1)) + Width*y]->getId() == 0) 
		{
			distance++;
		}
		break;
	case UP:
		while (GameObjects[(x + (Width*y - (distance + 1)))]->getId() == 0)
		{
			distance++;
		}
		break;
	case DOWN:
		while (GameObjects[(x + (Width*y - (distance - 1)))]->getId() == 0)
		{
			distance++;
		}
		break;
	}

	IwTrace(APP, ("distance is %d", distance));

	return distance;
}
