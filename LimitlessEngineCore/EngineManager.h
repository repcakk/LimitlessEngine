#pragma once
#include "stdafx.h"
#include <vector>

// Forward Declarations: 
class D3DGraphics;

class EngineManager
{
private:
	D3DGraphics *graphicsModule;
	std::vector<void (EngineManager::*)()> modulesToUpdate;

public:
	EngineManager();
	~EngineManager();

	void initGraphicsModule(HWND hWnd);

	void update();


private:
	void updateGraphics();
};

