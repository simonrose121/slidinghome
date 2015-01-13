#if !defined(__ROCK_H__)
#define __ROCK_H__

#include "gameObject.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Rock : public GameObject, CSprite
{
public:
	Rock() : GameObject() {}
	~Rock();
};

#endif