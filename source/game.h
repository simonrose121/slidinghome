#if !defined(__GAME_H__)
#define __GAME_H__

#include "grid.h"
#include "scene.h"

#define GRAPHIC_DESIGN_WIDTH	768

class Game : public Scene 
{
public:
	// Constructor & Destructor
	Game() : grid(0) {}
	~Game();

	// Member functions
	Grid* GetGrid(); // Not currently used
	void Init(int grid_width, int grid_height);
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void NewGame();
	static void	pauseMenu();
	float getGraphicsScale() { return graphicsScale; }
	bool getIsMoving() { return isMoving; }
	void setIsMoving(bool moving) { isMoving = moving; }

protected:
	// Member variables
	Grid* grid;
	CSprite* pauseButton;
	float graphicsScale;
	int start_x;
	int	start_y;
	bool isMoving;
	int minimumSwipe;
	int swipeOffset;
};

#endif