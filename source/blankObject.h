#if !defined(__BLANKOBJECT_H__)
#define __BLANKOBJECT_H__

#include "gameObject.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class BlankObject : public GameObject
{
public:
	BlankObject() {}
	~BlankObject();
};

#endif