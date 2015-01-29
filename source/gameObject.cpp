#include "gameObject.h"
#include "game.h"
#include "resources.h"
#include "main.h"

GameObject::~GameObject()
{

}

void GameObject::init(float x, float y, CIw2DImage* image)
{
	m_X = x;
	m_Y = y;

	SetImage(image);
}

void GameObject::setId(int id)
{
	objId = id;
}

int GameObject::getId()
{
	return objId;
}

void GameObject::updatePosition(float x, float y)
{
	IwTrace(APP, ("set position to [%f][%f]", x, y));

	m_X = x;
	m_Y = y;
}

void GameObject::setGridCoords(int x, int y)
{
	gridX = x;
	gridY = y;
}

std::pair<int, int> GameObject::getCoords()
{
	std::pair<int, int> coords = { gridX, gridY };
	return coords;
}