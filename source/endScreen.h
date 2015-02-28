#if !defined(__END_SCREEM_H__)
#define __END_SCREEN_H__

#include "scene.h"

class EndScreen : public Scene
{
public:
	// Constructor & Destructor
	EndScreen() {}
	~EndScreen();

	// Member functions
	void Init();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();
	static void	mainMenu();

private:
	// Member variables
	CSprite* exitButton;
	CSprite* playText;
};

#endif  // __END_SCREEN_H__