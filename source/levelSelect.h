#if !defined(__LEVEL_SELECT_H_)
#define __LEVEL_SELECT_H_

#define FONT_DESIGN_WIDTH 320
#define FONT_HEIGHT 15

#include "scene.h"

class LevelSelect : public Scene
{
public:
	LevelSelect() {}
	~LevelSelect();

	// initialise the menu
	void Init();

	// Update the menu
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void Render();

	float getFontScale() { return fontScale; }

	// Button callbacks
	static void	StartGame();

protected:
	// Member variables
	float graphicsScale;
	float fontScale;      
	float actualFontHeight;
	CSprite* levelButton;
	CSprite* playText;
	CLabel* levelLabel;
	int levelCount;
	int uiYPosition;

};

#endif