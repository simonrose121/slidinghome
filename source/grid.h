#if !defined(__GRID_H__)
#define __GRID_H__

#include "gameObject.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Grid
{
protected:
	GameObject**	GameObjects;
	int				Width, Height;
	int				GemSize;
	int				GridOriginX;
	int				GridOriginY;

public:
	GameObject*	getGameObject(int x, int y);

	Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width);
	~Grid();

	GameObject*	getGemScreen(int screen_x, int screen_y);
};

#endif