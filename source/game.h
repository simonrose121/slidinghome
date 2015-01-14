#if !defined(__GAME_H__)
#define __GAME_H__

#include "grid.h"
#include "scene.h"
#include "player.h"

#define GRAPHIC_DESIGN_WIDTH	768

class Game : public Scene 
{
protected:
	Grid*	grid;

	float	graphicsScale;
	int		start_x;
	int		start_y;

public:
	Game() : grid(0) {}
	~Game();

	Grid*	getGrid();
	float	getGraphicsScale()		{ return graphicsScale; }

	void	Init(int grid_width, int grid_height);
	void	Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void	Render();

	void	newGame();

private:
	std::string s;
};

#endif