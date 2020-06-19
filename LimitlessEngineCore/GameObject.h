#pragma once

#include <vector>
#include <map>
#include "StaticMesh.h"
#include "IComponentProvider.h"

// Forward Declaration
class IComponent;

class GameObject : 
	public IComponentProvider
{
private:
	std::map<std::string, IComponent*> components;

public:
	GameObject();
	GameObject(const GameObject& other);
	GameObject(GameObject &&other);
	virtual ~GameObject();
	GameObject& operator=(GameObject other);
	GameObject& operator=(GameObject&& other);
	friend void swap(GameObject &first, GameObject &second);
	void update();
	virtual IComponent* getComponent(std::string componentTypeName);
};

