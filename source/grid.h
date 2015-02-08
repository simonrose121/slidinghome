#if !defined(__GRID_H__)
#define __GRID_H__

#include "gameObject.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Grid
{
public:
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	// Constructor & Destruction
	Grid(CNode* scene, int num_columns, int num_rows, int offset_x, int offset_y, int grid_width);
	~Grid();

	// Member functions
	void MovePlayerLeft();
	void MovePlayerRight();
	void MovePlayerUp();
	void MovePlayerDown();
	void UpdatePosition(int index, int distance, Direction dir);
	void PrintGrid();
	void WinningState();
	void TestMap(Direction dir, int index);

	int	getWidth() const { return width; }
	int	getHeight() const { return height; }
	int	getGridOriginX() const { return gridOriginX; }
	int	getGridOriginY() const { return gridOriginY; }
	int	getGameObjectSize() const { return gameObjectSize; }
	int	getIndex();
	int	getDistance(Direction dir, int index);

protected:
	// Member variables
	GameObject** gameObjects;
	GameObject* player;
	int	homeIndex;
	int	width;
	int height;
	int	gridOriginX;
	int	gridOriginY;
	int	gameObjectSize;

	const float speedVal = 8.0;
};

#endif