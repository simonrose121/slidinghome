#include "gameObject.h"
#include "game.h"
#include "resources.h"
#include "main.h"

GameObject::~GameObject()
{

}

void GameObject::Init(float x, float y, CIw2DImage* image)
{
	m_X = x;
	m_Y = y;

	SetImage(image);
}

void GameObject::UpdatePosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}

void GameObject::setId(int id)
{
	objId = id;
}

void GameObject::setGridCoords(int x, int y)
{
	gridX = x;
	gridY = y;

	IwTrace(APP, ("i have been set to %d, %d", gridX, gridY));
}

std::pair<int, int> GameObject::getCoords()
{
	std::pair<int, int> coords(gridX, gridY);

	return coords;
}