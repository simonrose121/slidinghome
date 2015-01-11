#if !defined(__GAMEOBJECTS_H__)
#define __GAMEOBJECTS_H__

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class GameObjects  : public CSprite
{
protected:
	int		Type;
public:
	void	setType(int type);
	int		getType() const		{ return Type; }

	GameObjects() : Type(-1) {}
	~GameObjects();

	void	init(float x, float y, CAtlas* atlas);
};

#endif