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

	int index = 0;
	GridOriginX = offset_x;
	GridOriginY = IwGxGetScreenHeight() - (num_rows * GameObjectSize) - offset_y;
	for (int y = 0; y < num_rows; y++)
	{
		for (int x = 0; x < num_columns; x++)
		{
			switch (map[x][y])
			{
			case 0:
				GameObjects[index] = new BlankObject();
				GameObjects[index]->setId(0);
				scene->AddChild(GameObjects[index]);
				index++;
				break;

			case 1:
				GameObjects[index] = new Rock();
				GameObjects[index]->setId(1);
				GameObjects[index]->init((float)x * GameObjectSize + GridOriginX, GridOriginY + (float)y * GameObjectSize, g_pResources->GetRock());
				GameObjects[index]->m_ScaleX = gem_scale;
				GameObjects[index]->m_ScaleY = gem_scale;
				scene->AddChild(GameObjects[index]);
				index++;
				break;

			case 2:
				GameObjects[index] = new Player();
				PlayerIndex = index;
				GameObjects[index]->setId(2);
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
	//get player
	Player* player = (Player*)GameObjects[PlayerIndex];

	//get distance that player can move

	IwTrace(APP, ("player is at %d", PlayerIndex));

	int distance = getDistance(LEFT);
	
	Game* game = (Game*)g_pSceneManager->Find("game");

	float new_X = player->m_Y - (distance * GameObjectSize);

	game->GetTweener().Tween(0.5f,
						FLOAT, &new_X, player->m_Y,
						FLOAT, &player->m_X, player->m_Y,
						EASING, Ease::sineInOut,
						END);
}

int Grid::getDistance(Grid::Direction dir)
{
	int distance = 0;

	switch (dir)
	{
	case LEFT:
			{
				 int i = GameObjects[PlayerIndex - 1]->getId();
				 IwTrace(APP, ("to the left is %d", i));

				 if (i == 0)
				 {
					 while (i != 1)
					 {
						 distance++;

						 if (GameObjects[PlayerIndex - distance]->getId() != NULL)
						 {
							 i = GameObjects[PlayerIndex - distance]->getId();
						 }
						 IwTrace(APP, ("distance is %d", distance));
					 }

					 return distance - 1;
				 }
				 break;
			}
	case RIGHT:
		break;
	case UP:
		break;
	case DOWN:
		break;
	}
}
