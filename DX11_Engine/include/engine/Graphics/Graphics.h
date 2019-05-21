#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <wrl/client.h>

namespace TrepiCoder {
	class Graphics {
	public:
		bool initialize(HWND hwnd, int width, int height);

	private:
		bool initDirectX(HWND hwnd, int width, int height);

		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	};
}
