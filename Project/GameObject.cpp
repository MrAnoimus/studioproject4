#include "GameObject.h"

int GameObject::counter = 0;
GameObject::GameObject(GAMEOBJECT_TYPE typeValue) 
	: type(typeValue),
	scale(1, 1, 1),
	active(false)
{
}

GameObject::~GameObject()
{
}