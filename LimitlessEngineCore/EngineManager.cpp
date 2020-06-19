#include "EngineManager.h"
#include "D3DGraphics.h"
#include "VertexTypes.h"

EngineManager::EngineManager()
{
}

EngineManager::~EngineManager()
{
	delete this->graphicsModule;
}

void EngineManager::initGraphicsModule(HWND hWnd)
{
	// Initiale D3DGraphics module with hWnd:
	this->graphicsModule = new D3DGraphics(hWnd);
	
	// Register graphics for update:
	this->modulesToUpdate.push_back(&EngineManager::updateGraphics);
}

// Example Geometry TEMPORARY TODO remove
std::vector<Vertex> vertices =
{
	{ 0.0f, 0.5f, 0.0f,{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ 0.45f, -0.5, 0.0f,{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ -0.45f, -0.5f, 0.0f,{ 0.0f, 0.0f, 1.0f, 1.0f } }
};

std::vector<unsigned int> indices = { 0, 1, 2 };


void EngineManager::update()
{
	// Update all modules:
	for (void (EngineManager::*updateModulePtr)() : this->modulesToUpdate)
	{
		(this->*updateModulePtr)();
	}
}

void EngineManager::updateGraphics()
{
	// Drawing code:
	this->graphicsModule->ClearFrame(new float[4]{ 0.4f, 0.4f, 0.1f, 1.0f });
	this->graphicsModule->DrawGeometryData(vertices, indices);
	this->graphicsModule->PresentFrame();

	// Present rendered image to user, call after all drawing commands:
	this->graphicsModule->PresentFrame();
}
