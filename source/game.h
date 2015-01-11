#if !defined(__GAME_H__)
#define __GAME_H__

#include "grid.h"
#include "scene.h"

#define GRAPHIC_DESIGN_WIDTH	768

class Game : public Scene 
{
protected:
	float	graphicsScale;

public:
	float	getGraphicsScale()		{ return graphicsScale; }

	~Game();
	void	Init(int grid_width, int grid_height);

	void	newGame();
};

#endif