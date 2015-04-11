#if !defined(__MAIN_MENU_H__)
#define __MAIN_MENU_H__

#include "scene.h"

/*
	Main menu scene
*/
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
	void SetSound();
	void SetMusic();

	// Getters
	float getGraphicsScale() { return graphicsScale; }
	bool getHighContrastMode() { return changeToHighContrast; }
	CSprite* getSoundButtonHome() { return soundButtonHome; }
	CSprite* getMusicButtonHome() { return musicButtonHome; }

	// Setters
	void setHighContrastMode(bool highContrastMode) { changeToHighContrast = highContrastMode; }

private:
	// Member variables
	float graphicsScale;
	CSprite* background;
	CSprite* playButton;
	CSprite* settingsButton;
	CSprite* soundButtonHome;
	CSprite* musicButtonHome;
	bool changeToHighContrast;
};

#endif  // __MAIN_MENU_H__