#if !defined(__PAUSEMENU_H__)
#define __PAUSEMENU_H__

#include "scene.h"

class PauseMenu : public Scene
{
public:
	// Constructor & Destructor
	PauseMenu() {}
	~PauseMenu();

	// Member functions
	void Init();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	static void	mainMenu();
	static void	StartGame();
	void ChangeBackground();

	bool getHighContrastMode() { return changeToHighContrast; }
	void setHighContrastMode(bool highContrastMode){ changeToHighContrast = highContrastMode; }

	// Button callbacks

private:
	// UI components
	CSprite* exitButton;
	CSprite* playButton;
	CSprite* playText;
	CSprite* background = new CSprite();
	bool changeToHighContrast;
};

#endif  // __PAUSEMENU_H__