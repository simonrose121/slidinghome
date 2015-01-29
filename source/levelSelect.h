#if !defined(__LEVELSELECT_H_)
#define __LEVELSELECT_H_

#include "scene.h"

class LevelSelect : public Scene
{
protected:
	// UI components

public:
	LevelSelect() {}
	~LevelSelect();

	// initialise the menu
	void Init();

	// Update the menu
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

	// Render the menu
	void Render();

	// Button callbacks

};

#endif