#if !defined(__LEVEL_SELECT_H_)
#define __LEVEL_SELECT_H_
#define FONT_DESIGN_WIDTH 320

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

	static void	StartGame();

	// Button callbacks

protected:
	// Member variables
	float graphicsScale;
	float fontScale;                      // Font is correct size on 320 wide screen so we scale to match native screen size
	float actualFontHeight;               // The actual pixel height of the font
	CSprite* levelButton;
	CSprite* playText;
	CLabel* levelLabel;
	int levelCount;
	int uiYPosition;

public:
	float getFontScale() { return fontScale; }
};

#endif