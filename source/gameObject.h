#if !defined(__gameObject_H__)
#define __gameObject_H__

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class GameObject : public CSprite
{
protected:
	int			objId;
	int			gridX;
	int			gridY;

public:
	GameObject() { }
	~GameObject();

	void		init(float x, float y, CIw2DImage* image);


	void		updatePosition(float x, float y);

	void		setId(int id);
	void		setGridCoords(int x, int y);

	int			getId();
	std::pair<int, int> getCoords();
};

#endif