#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DCompiler.lib")


#include "stdafx.h"
#include "D3DGraphics.h"
#include "ScreenProperties.h"
#include <D3Dcompiler.h>
#include <vector>
#include "VertexTypes.h"

D3DGraphics::D3DGraphics(HWND hWnd)
{
	this->InitD3D(hWnd);
}

D3DGraphics::~D3DGraphics()
{
	this->CleanD3D();
}

void D3DGraphics::ClearFrame(float RGBA[])
{
	this->deviceContext->ClearRenderTargetView(this->renderTargetView, RGBA);
}


void D3DGraphics::DrawGeometryData(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	const size_t vertexSize = sizeof(Vertex);
	const size_t verticessDataSize = vertexSize * vertices.size();

	if(this->vertexBufferSize < verticessDataSize)
	{
		//if (this->vertexBuffer)
			//this->vertexBuffer->Release();
		
		this->vertexBufferSize = verticessDataSize;
		this->CreateBuffer(vertexSize, vertices.size(), D3D11_BIND_VERTEX_BUFFER, &this->vertexBuffer);

		UINT offset = 0;
		UINT stride = static_cast<UINT>(vertexSize);
		this->deviceContext->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stride, &offset);
	}

	this->FillBuffer(vertices.data(), verticessDataSize, this->vertexBuffer);

	const size_t indexSize = sizeof(unsigned int);
	const size_t indicesDataSize = indexSize * indices.size();

	if (this->indexBufferSize < indicesDataSize)
	{
		//if(this->indexBuffer)
			//this->indexBuffer->Release();
		this->indexBufferSize = indicesDataSize;
		this->CreateBuffer(indexSize, indices.size(), D3D11_BIND_INDEX_BUFFER, &this->indexBuffer);

		UINT stride = static_cast<UINT>(indexSize);
		this->deviceContext->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	this->FillBuffer(indices.data(), indicesDataSize, this->indexBuffer);

	this->deviceContext->DrawIndexed(static_cast<UINT>(indices.size()), 0, 0);
}

void D3DGraphics::PresentFrame()
{
	this->swapChain->Present(0, 0);
}

void D3DGraphics::InitD3D(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &this->swapChain, &this->device, NULL, &this->deviceContext);

	this->CreateBackBuffer();
	this->CreateViewport();
	this->CreatePipeline();
}

void D3DGraphics::CreateBackBuffer()
{
	ID3D11Texture2D *backBuffer;
	this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	this->device->CreateRenderTargetView(backBuffer, NULL, &this->renderTargetView);
	backBuffer->Release();

	this->deviceContext->OMSetRenderTargets(1, &this->renderTargetView, NULL);
}

void D3DGraphics::CreateViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;

	this->deviceContext->RSSetViewports(1, &viewport);
}

void D3DGraphics::CreatePipeline()
{
	ID3D10Blob *vsBlob, *psBlob;
	
	HRESULT result;
	
	result = D3DReadFileToBlob(L"../LimitlessEngineGraphics/Debug/VertexShader.cso", &vsBlob);
	result = D3DReadFileToBlob(L"../LimitlessEngineGraphics/Debug/PixelShader.cso", &psBlob);

	result = this->device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &this->vertexShader);
	result = this->device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &this->pixelShader);

	this->deviceContext->VSSetShader(this->vertexShader, 0, 0);
	this->deviceContext->PSSetShader(this->pixelShader, 0, 0);


	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	result = this->device->CreateInputLayout(inputElementDesc, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &this->inputLayout);

	this->deviceContext->IASetInputLayout(this->inputLayout);

	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vsBlob->Release();
	psBlob->Release();
}

void D3DGraphics:: CreateBuffer(size_t elementSize, size_t elementCount, D3D11_BIND_FLAG bindFlag, ID3D11Buffer **buffer)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = static_cast<UINT>(elementSize * elementCount);
	vertexBufferDesc.BindFlags = bindFlag;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	HRESULT result;

	result = this->device->CreateBuffer(&vertexBufferDesc, NULL, buffer);
}

void D3DGraphics::FillBuffer(void * data, size_t dataSize, ID3D11Buffer *buffer)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	this->deviceContext->Map(buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresource);
	memcpy(mappedSubresource.pData, data, dataSize);
	this->deviceContext->Unmap(buffer, NULL);
}

void D3DGraphics::CleanD3D()
{
	this->swapChain->SetFullscreenState(FALSE, NULL);
	
	this->vertexBuffer->Release();
	this->vertexShader->Release();
	this->pixelShader->Release();
	this->swapChain->Release();
	this->renderTargetView->Release();
	this->device->Release();
	this->deviceContext->Release();
}