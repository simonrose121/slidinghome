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
				scene->AddChild(GameObjects[x + Width*y]);
				break;

			case 1:
				IwTrace(APP, ("GameObject[%d], Id(%d)", x + Width*y, 1));
				GameObjects[x + Width*y] = new Rock();
				GameObjects[x + Width*y]->setId(1);
				GameObjects[x + Width*y]->init((float)x * GameObjectSize + GridOriginX, GridOriginY + (float)y * GameObjectSize, g_pResources->GetRock());
				GameObjects[x + Width*y]->m_ScaleX = gem_scale;
				GameObjects[x + Width*y]->m_ScaleY = gem_scale;
				scene->AddChild(GameObjects[x + Width*y]);
				break;

			case 2:
				IwTrace(APP, ("GameObject[%d], Id(%d)", x + Width*y, 2));
				GameObjects[x + Width*y] = new Player();
				GameObjects[x + Width*y]->setId(2);
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
	Player* player = (Player*)GameObjects[PlayerIndex];
	Game* game = (Game*)g_pSceneManager->Find("game");

	IwTrace(APP, ("player is at %f, %f", player->m_X, player->m_Y));

	int distance = getDistance(LEFT);

	float speed = (float)(distance / 8);

	float new_X = player->m_X - (distance * GameObjectSize);

	PlayerIndex = PlayerIndex - distance;

	game->GetTweener().Tween(speed,
						FLOAT, &player->m_X, new_X,
						EASING, Ease::sineInOut,
						END);

	player->updatePosition(new_X, player->m_Y);

	IwTrace(APP, ("player is now at %f, %f", player->m_X, player->m_Y));
}

void Grid::movePlayerRight()
{
	Player* player = (Player*)GameObjects[PlayerIndex];
	Game* game = (Game*)g_pSceneManager->Find("game");

	IwTrace(APP, ("player is at %f, %f", player->m_X, player->m_Y));

	int distance = getDistance(RIGHT);

	float speed = (float)(distance / 8);

	float new_X = player->m_X + (distance * GameObjectSize);

	game->GetTweener().Tween(speed,
		FLOAT, &player->m_X, new_X,
		EASING, Ease::sineInOut,
		END);

	player->updatePosition(new_X, player->m_Y);

	IwTrace(APP, ("player is now at %f, %f", player->m_X, player->m_Y));
}

void Grid::movePlayerUp()
{

}

void Grid::movePlayerDown()
{

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
			{
				int i = GameObjects[PlayerIndex + 1]->getId();
				IwTrace(APP, ("to the right is %d", i));

				if (i == 0)
				{
					while (i != 1)
					{
						distance++;

						if (GameObjects[PlayerIndex + distance]->getId() != NULL)
						{
							i = GameObjects[PlayerIndex + distance]->getId();
						}
						IwTrace(APP, ("distance is %d", distance));
					}
					return distance - 1;
				}
			}
	case UP:
		break;
	case DOWN:
		break;
	}
}
