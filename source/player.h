#if !defined(__PLAYER_H__)
#define __PLAYED_H__

#include "gameObject.h"
#include "main.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Player : public GameObject
{
protected:

public:
	Player() {}
	~Player();
};

#endif