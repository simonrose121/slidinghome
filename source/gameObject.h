#if !defined(__gameObject_H__)
#define __gameObject_H__

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class GameObject : public CSprite
{
protected:
	int		Type;
public:
	void	setType(int type);
	int		getType() const		{ return Type; }

	GameObject() { }
	~GameObject();

	void	init(float x, float y, CIw2DImage* image);
};

#endif