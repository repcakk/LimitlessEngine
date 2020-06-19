#include "stdafx.h"
#include "GameObject.h"
#include "IComponent.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const GameObject &other)
	: components(other.components)
{
}

GameObject::GameObject(GameObject &&other)
	: components(other.components)
{
}

GameObject::~GameObject()
{
	for (std::pair<std::string, IComponent*> components : this->components)
	{
		delete components.second;
	}
}

GameObject& GameObject::operator=(GameObject other)
{
	swap(*this, other);
	return *this;
}

GameObject & GameObject::operator=(GameObject &&other)
{
	swap(*this, other);
	return *this;
}


void swap(GameObject &first, GameObject &second)
{
	using std::swap;
	swap(first.components, second.components);
}

void GameObject::update()
{
}

IComponent* GameObject::getComponent(std::string componentTypeName)
{
	try
	{
		return this->components.at(componentTypeName);
	}
	catch (const std::out_of_range&)
	{
		return nullptr;
	}
}
