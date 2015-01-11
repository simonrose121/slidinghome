#if !defined(__GRID_H__)
#define __GRID_H__

#include "gameObjects.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Grid
{
protected:
	GameObjects**	GameObjects;
	int				Width, Height;
	int				GemSize;
	int				GridOriginX;
	int				GridOriginY;

public:
	GameObjects*	getGameObject(int x, int y);

	Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width);
	~Grid();

	GameObjects*	getGemScreen(int screen_x, int screen_y);
};

#endif