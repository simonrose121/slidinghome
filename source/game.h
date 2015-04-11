#if !defined(__GAME_H__)
#define __GAME_H__

#include "grid.h"
#include "scene.h"

#define GRAPHIC_DESIGN_WIDTH	768

/*
	Game class is a scene runs the gameplay
	Holds an instance of the grid
*/
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
	void Init();
	void InitOnScreenButtons();
	void CleanupOnScreenButtons();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	void NewGame(std::string levelNo, int width, int height);
	void EndGame();
	static void	MoveToPauseMenu();
	void ChangeBackground();
	void CleanLevelCompletePopup();
	void InitLevelCompletePopup();
	void InitInstructions();
	void CleanupInstructions();
	void UpdateSwitches();
	bool IsComplete();

	// Getters
	float getGraphicsScale() { return graphicsScale; }
	bool getIsMoving() { return isMoving; }
	bool getShowOnScreenButtons() { return showOnScreenButtons; }
	bool getHighContrastMode() { return changeToHighContrast; }
	std::string getLevelNum() { return levelNum; }

	// Setters
	void setIsMoving(bool moving) { isMoving = moving; }
	void setShowOnScreenButtons(bool onScreenButtons) { showOnScreenButtons = onScreenButtons; }
	void setHighContrastMode(bool highContrastMode){ changeToHighContrast = highContrastMode; }
	

private:
	// Member variables
	Grid* grid;
	CSprite* background;
	CSprite* pauseButton;
	CSprite* resetButton;
	CSprite* upButton;
	CSprite* rightButton;
	CSprite* downButton;
	CSprite* leftButton;
	CSprite* star;
	CSprite* nextText;
	CSprite* levelComplete;
	CSprite* allText;
	CSprite* levelInfo;
	CSprite* instructions;
	float graphicsScale;
	float buttonScale;
	int start_x;
	int	start_y;
	bool isMoving;
	int minimumSwipe;
	int swipeOffset;
	bool pressedDown;
	State currentState;
	bool showOnScreenButtons;
	bool changeToHighContrast;
	bool instructionsOn;
	bool hasMoved;
	std::string levelNum;
};

#endif