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
	static void	StartGame();

protected:
	// Member variables
	CSprite* playButton;
	CSprite* playText;
};

#endif  // __MAIN_MENU_H__