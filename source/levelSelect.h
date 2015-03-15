#if !defined(__LEVEL_SELECT_H_)
#define __LEVEL_SELECT_H_

#include "scene.h"

#define LEVEL_COUNT 7

class LevelSelect : public Scene
{
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
	static void	StartGame(std::string levelNo);
	void MoveToMainMenu();

	void LevelStars();
	void RemoveLevelStars();

private:
	// Member variables
	float graphicsScale;
	CSprite* level1;
	CSprite* level2;
	CSprite* level3;
	CSprite* level4;
	CSprite* level5;
	CSprite* level6;
	CSprite* level7;
	CSprite* playText;
	CSprite* backButton;
	CSprite* star;
};

#endif