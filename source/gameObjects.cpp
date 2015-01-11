#include "gameObjects.h"
#include "game.h"
#include "resources.h"
#include "main.h"

GameObjects::~GameObjects()
{

}

void GameObjects::init(float x, float y, CAtlas* atlas)
{
	m_X = x;
	m_Y = y;
	SetAtlas(atlas);
}

