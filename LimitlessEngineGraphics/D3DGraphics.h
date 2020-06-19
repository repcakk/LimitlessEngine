#pragma once

#include <d3d11.h>
#include <DXGI1_2.h>
#include <vector>

// Forward Declaration
struct Vertex;

class D3DGraphics
{
private:
	IDXGISwapChain *swapChain;
	ID3D11Device *device;
	ID3D11DeviceContext *deviceContext;

	ID3D11RenderTargetView *renderTargetView;
	ID3D11RasterizerState *rasterizerState;

	// Shaders
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;

	// Buffers
	ID3D11Buffer *vertexBuffer;
	size_t vertexBufferSize = 0;

	ID3D11Buffer *indexBuffer;;
	size_t indexBufferSize = 0;

	// Input layout
	ID3D11InputLayout *inputLayout;

public:
	D3DGraphics(HWND hWnd);
	~D3DGraphics();
	void ClearFrame(float RGBA[]);
	void DrawGeometryData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void PresentFrame();


private:
	D3DGraphics();
	void InitD3D(HWND hWnd);
	void CreateBackBuffer();
	void CreateViewport();
	void CreatePipeline();
	void CreateBuffer(size_t elementSize, size_t elementCount, D3D11_BIND_FLAG bindFlag, ID3D11Buffer **buffer);
	void FillBuffer(void *vertexData, size_t dataSize, ID3D11Buffer *buffer);
	void CleanD3D();
};

