#if !defined(__gameObject_H__)
#define __gameObject_H__

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class GameObject : public CSprite
{
protected:
	std::string name;

public:
	GameObject() { }
	~GameObject();

	void	setName(std::string name);

	void	init(float x, float y, CIw2DImage* image);
};

#endif