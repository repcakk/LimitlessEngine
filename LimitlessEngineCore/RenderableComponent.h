#pragma once
#include "IComponent.h"

// Forward Declaration
class GameObject;

class RenderableComponent :
	public IComponent
{
public:
	RenderableComponent();
	virtual ~RenderableComponent();
	virtual void attachTo(GameObject *gameObject);
	virtual void update();
};

