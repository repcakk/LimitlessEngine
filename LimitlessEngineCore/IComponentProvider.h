#pragma once
#include <string>
class IComponent;

class IComponentProvider
{
public:
	virtual IComponent* getComponent(std::string componentTypeName) = 0;
};

