#include "IwGx.h"
#include "IwTween.h"
#include "audio.h"
#include "scene.h"
#include "grid.h"
#include "game.h"
#
#include "resources.h"
#include "main.h"

using namespace IwTween;

Grid::Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width)
{
	Width = num_columns;
	Height = num_rows;
	GameObjects = new GameObject* [num_columns * (num_rows + 1)];

	int bm_width = (int)g_pResources->GetRock()->GetWidth();
	GemSize = (IwGxGetScreenWidth() * bm_width) / GRAPHIC_DESIGN_WIDTH;

	float gem_scale = (float)GemSize / bm_width;

	int index = 0;
	GridOriginX = offset_x;
	GridOriginY = IwGxGetScreenHeight() - (num_rows * GemSize) - offset_y;
	for (int y = 0; y < num_rows; y++)
	{
		for (int x = 0; x < num_columns; x++)
		{
			// Init gem
			GameObjects[index] = new Rock();
			GameObjects[index]->init((float)x * GemSize + GridOriginX, GridOriginY + (float)y * GemSize, g_pResources->GetRock());
			GameObjects[index]->m_ScaleX = gem_scale;
			GameObjects[index]->m_ScaleY = gem_scale;
			// Add to scene
			scene->AddChild(GameObjects[index]);
			index++;
		}
	}
	// We fill extra row with 1 to give lowest line of blocks something solid to rest on
	for (int x = 0; x < num_columns; x++)
		GameObjects[index++] = (GameObject*)1;
}

Grid::~Grid()
{
	if (GameObjects != 0)
		delete[] GameObjects;
}