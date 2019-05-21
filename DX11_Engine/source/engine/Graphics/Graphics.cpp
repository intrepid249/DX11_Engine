#include "engine/Graphics/Graphics.h"
#include "engine/Graphics/AdapterReader.h"

#include <vector>

namespace TrepiCoder {
	bool Graphics::initialize(HWND hwnd, int width, int height)
	{
		if (!initDirectX(hwnd, width, height))
			return false;

		// Initialize shaders, scene, etc

		return true;
	}

	void Graphics::renderFrame()
	{
		float bgColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), bgColor);
		m_swapchain->Present(
			1, // VSSYNC - 1 Enabled | 0 Disabled
			NULL
		);
	}

	bool Graphics::initDirectX(HWND hwnd, int width, int height)
	{
		std::vector<AdapterData> adapters = AdapterReader::getAdapters();

		if (adapters.size() < 1) {
			ErrorLogger::Log("No DXGI Adapters found");
			return false;
		}

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		scd.BufferDesc.Width = width;
		scd.BufferDesc.Height = height;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;

		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 1;
		scd.OutputWindow = hwnd;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			adapters[0].m_pAdapter, // IDXGI Adapter
			D3D_DRIVER_TYPE_UNKNOWN,
			NULL, // Software driver type
			NULL, // Flags for runtime layers
			NULL, // Feature levels array
			0, // # of feature levels in array
			D3D11_SDK_VERSION,
			&scd, // Swap chain description
			m_swapchain.GetAddressOf(),
			m_device.GetAddressOf(),
			NULL,
			m_deviceContext.GetAddressOf()
		);

		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to create device and swapchain");
			return false;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		hr = m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to retrieve BackBuffer");
			return false;
		}

		hr = m_device->CreateRenderTargetView(backBuffer.Get(), NULL, m_renderTargetView.GetAddressOf());
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to create render target view");
			return false;
		}

		m_deviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), NULL);

		return true;
	}
}
