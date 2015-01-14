#if !defined(__GRID_H__)
#define __GRID_H__

#include "gameObject.h"
#include "rock.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Grid
{
protected:
	GameObject**	GameObjects;
	int				Width, Height;
	int				GameObjectSize;
	int				GridOriginX;
	int				GridOriginY;

public:
	int				getWidth() const			{ return Width; }
	int				getHeight() const			{ return Height; }
	int				getGridOriginX() const		{ return GridOriginX; }
	int				getGridOriginY() const		{ return GridOriginY; }
	int				getGameObjectSize() const	{ return GameObjectSize; }

	Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width);
	~Grid();

	void			screenToGrid(int x, int y, int& out_x, int& out_y);
};

#endif