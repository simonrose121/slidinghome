#if !defined(__gameObject_H__)
#define __gameObject_H__

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

/*
	GameObjects are used in the grid to represent all game assets
*/
class GameObject : public CSprite
{
public:
	// Constructor & Destructor
	GameObject() { }
	~GameObject();

	// Member functions
	void Init(float x, float y, CIw2DImage* image);
	void Init(float x, float y, CAtlas* atlas);
	void UpdatePosition(float x, float y);

	void setId(int id);
	void setGridCoords(int x, int y);
	int	getId() { return objId; }
	std::pair<int, int> getCoords();

private:
	// Member variables
	int	objId;
	int	gridX;
	int	gridY;
};

#endif