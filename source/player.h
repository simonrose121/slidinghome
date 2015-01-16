#if !defined(__PLAYER_H__)
#define __PLAYED_H__

#include "gameObject.h"
#include "main.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class Player : public GameObject
{
private:
	int				PlayerX;
	int				PlayerY;

public:
	Player(int x, int y) : PlayerX(x), PlayerY(y) {}
	~Player();

	void			moveLeft();

	void			setPlayerCoordinates(int x, int y);

	int				getPlayerX()		{ return PlayerX; }
	int				getPlayerY()		{ return PlayerY; }
};

#endif