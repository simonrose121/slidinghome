#if !defined(__GRID_H__)
#define __GRID_H__

#include "scene.h"
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
	Grid(CNode* scene);
	~Grid();

	// Member functions
	void MovePlayerLeft();
	void MovePlayerRight();
	void MovePlayerUp();
	void MovePlayerDown();
	void GenerateLevel(std::string levelId, int num_columns, int num_rows, int grid_width, float graphicsScale);
	void ClearLevel();
	void ResetPlayer();
	
	int	getWidth() const { return width; }
	int	getHeight() const { return height; }
	int	getGridOriginX() const { return gridOriginX; }
	int	getGridOriginY() const { return gridOriginY; }
	int	getGameObjectSize() const { return gameObjectSize; }
	int	getIndex();
	int	getDistance(Direction dir);
	
private:
	enum ObjectIds {
		BLANK = 0,
		EDGE = 1,
		ROCK = 2,
		PLAYER = 3,
		HOME = 4,
		SNOWPATCH = 5,
		SWITCH = 6,
		SWITCHROCK = 7,
		SWITCHROCKINVISIBLE = 8
	};

	// Member variables
	GameObject** gameObjects;
	GameObject* player;
	int playerIndex;
	int	width;
	int height;
	int initialIndex;
	int	gridOriginX;
	int	gridOriginY;
	int	gameObjectSize;
	float speedVal;
	CNode* game;
	bool onSnowPatch;
	std::string levelNum;
	bool switchPressed;

	// Private member functions
	void SwitchPressed(int switchIndex);
	void CheckIfOnSnowpatch();
	void UpdatePosition(int distance, Direction dir);
	void PrintGrid();
	bool TestMap(Direction dir);
	static void WinningState(CTween* pTween);
	static void SetComplete(CTween* pTween);
	void MovePlayer(Direction dir, float newPos, int distance);
};

#endif