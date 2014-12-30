#if !defined(__MAINEMENU_H__)
#define __MAINEMENU_H__

#include "scene.h"

class PauseMenu : public Scene
{
protected:
	// UI components

public:
	PauseMenu() {}
	~PauseMenu();

	// initialise the menu
	void            Init();

	// Update the menu
	void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void            Render();

	// Button callbacks

};

#endif  // __MAINEMENU_H__