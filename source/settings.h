#if !defined(__SETTINGS_H__)
#define __SETTINGS_H__

#include "scene.h"

class Settings : public Scene
{
public:
	// Constructor & Destructor
	Settings() {}
	~Settings();

	// Member functions
	void Init();
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	void Render();

	// Button callbacks
	void SetOnScreenButtons();

protected:
	// UI components
	CSprite* showOnScreenButtons;
};

#endif  // __SETTINGS_H__