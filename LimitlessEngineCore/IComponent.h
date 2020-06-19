#pragma once

// Forward declaration
class GameObject;
class IComponentProvider;

class IComponent
{
protected:
	IComponentProvider *parentComponentsProvider;
public:
	virtual void attachTo(GameObject *gameObject) = 0;
	virtual void update() = 0;
};

