#include "IwGx.h"
#include "IwTween.h"
#include "audio.h"
#include "scene.h"
#include "grid.h"
#include "game.h"
#include "resources.h"
#include "main.h"

using namespace IwTween;

Grid::Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width)
{
	Width = num_columns;
	Height = num_rows;
	GameObjects = new GameObject* [num_columns * (num_rows + 1)];

	//create gems
}

Grid::~Grid()
{
	if (GameObjects != 0)
		delete[] GameObjects;
}