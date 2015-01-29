#if !defined(__MAINEMENU_H__)
#define __MAINEMENU_H__

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

	// Button callbacks

protected:
	// UI components
};

#endif  // __MAINEMENU_H__