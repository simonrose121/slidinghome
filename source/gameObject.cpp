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
	IwTrace(APP, ("setting name to %d", id));
	objId = id;
}

int GameObject::getId()
{
	return objId;
}

void GameObject::updatePosition(float x, float y)
{
	m_X = x;
	m_Y = y;
}