#if !defined(__GAME_H__)
#define __GAME_H__

#include "grid.h"
#include "scene.h"

#define GRAPHIC_DESIGN_WIDTH	768

class Game : public Scene 
{
public:
	enum State {
		PAUSED,
		COMPLETE,
		INPROGRESS
	};

	// Constructor & Destructor
	Game() : grid(0) {}
	~Game();

	// Member functions
	Grid* GetGrid(); // Not currently used
	void Init();
	void InitOnScreenButtons();
	void CleanupOnScreenButtons();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void NewGame(int width, int height);
	void EndGame();
	static void	ToPauseMenu();


	float getGraphicsScale() { return graphicsScale; }
	bool getIsMoving() { return isMoving; }
	bool getShowOnScreenButtons() { return showOnScreenButtons; }

	void setIsMoving(bool moving) { isMoving = moving; }
	void setShowOnScreenButtons(bool onScreenButtons) { showOnScreenButtons = onScreenButtons; }


protected:
	// Member variables
	Grid* grid;
	CSprite* pauseButton;
	CSprite* upButton;
	CSprite* rightButton;
	CSprite* downButton;
	CSprite* leftButton;
	CSprite* star;
	CSprite* holostar;
	float graphicsScale;
	int start_x;
	int	start_y;
	bool isMoving;
	int minimumSwipe;
	int swipeOffset;
	bool pressedDown;
	State currentState;
	bool showOnScreenButtons;
};

#endif