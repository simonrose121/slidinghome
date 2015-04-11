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
	void SetSound();
	void SetMusic();

	bool getHighContrastMode() { return changeToHighContrast; }
	void setHighContrastMode(bool highContrastMode){ changeToHighContrast = highContrastMode; }

	CSprite* getSoundButtonPause() { return soundButtonPause; }
	CSprite* getMusicButtonPause() { return musicButtonPause; }

private:
	// UI components
	CSprite* exitButton;
	CSprite* playButton;
	CSprite* playText;
	CSprite* background;
	CSprite* soundButtonPause;
	CSprite* musicButtonPause;
	bool changeToHighContrast;
};

#endif  // __PAUSEMENU_H__