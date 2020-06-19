#include "stdafx.h"
#include "RenderableComponent.h"
#include "GameObject.h"

RenderableComponent::RenderableComponent()
{
}

RenderableComponent::~RenderableComponent()
{
}

void RenderableComponent::attachTo(GameObject *gameObject)
{
	// Add attach code
	// gameObject->attach...

	this->parentComponentsProvider = dynamic_cast<IComponentProvider*>(gameObject);

}

void RenderableComponent::update()
{
	//Get transform component
	parentComponentsProvider->getComponent("RenderableComponent");

}
