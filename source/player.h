#if !defined(__PLAYER_H__)
#define __PLAYED_H__

#include "gameObject.h"
#include "main.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Player : public GameObject
{
public:
	// Constructor & Destructor
	Player() {}
	~Player();

	// Member functions
	void MoveLeft(int distance);
	void MoveRight(int distance);
};

#endif