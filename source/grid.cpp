#include "IwGx.h"
#include "IwTween.h"
#include "audio.h"
#include "scene.h"
#include "grid.h"
#include "game.h"
#include <fstream>
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

	int index = 0;
	GridOriginX = offset_x;
	GridOriginY = IwGxGetScreenHeight() - (num_rows * GameObjectSize) - offset_y;
	for (int y = 0; y < num_rows; y++)
	{
		for (int x = 0; x < num_columns; x++)
		{
			switch (map[x][y])
			{
			case 1:
				GameObjects[index] = new Rock();
				GameObjects[index]->init((float)x * GameObjectSize + GridOriginX, GridOriginY + (float)y * GameObjectSize, g_pResources->GetRock());
				GameObjects[index]->m_ScaleX = gem_scale;
				GameObjects[index]->m_ScaleY = gem_scale;
				scene->AddChild(GameObjects[index]);
				index++;
				break;

			case 2:
				GameObjects[index] = new Player(x, y);
				GameObjects[index]->init((float)x * GameObjectSize + GridOriginX, GridOriginY + (float)y * GameObjectSize, g_pResources->GetPlayer());
				GameObjects[index]->m_ScaleX = gem_scale;
				GameObjects[index]->m_ScaleY = gem_scale;
				scene->AddChild(GameObjects[index]);
				index++;
				break;
			}
		}
	}

	for (int x = 0; x < num_columns; x++)
		GameObjects[index++] = (GameObject*)1;
}

Grid::~Grid()
{
	if (GameObjects != 0)
		delete[] GameObjects;
}

void Grid::movePlayerLeft()
{
	//get current player location


	//check grid location to the left

	//get distance that player can move

	//move the player to that spot using a tween (call method on player)

}
