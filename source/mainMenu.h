#if !defined(__MAIN_MENU_H__)
#define __MAIN_MENU_H__

#include "scene.h"

class MainMenu : public Scene
{
public:
	// Constructor & Destructor
	MainMenu() {}
	~MainMenu();

	// Member functions
	void Init();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	static void	MoveToLevelSelect();
	static void MoveToSettings();
	void ChangeBackground();

	float getGraphicsScale() { return graphicsScale; }
	bool getHighContrastMode() { return changeToHighContrast; }

	void setHighContrastMode(bool highContrastMode){ changeToHighContrast = highContrastMode; }

protected:
	// Member variables
	float graphicsScale;
	CSprite* background;
	CSprite* playButton;
	CSprite* settingsButton;
	bool changeToHighContrast;
};

#endif  // __MAIN_MENU_H__