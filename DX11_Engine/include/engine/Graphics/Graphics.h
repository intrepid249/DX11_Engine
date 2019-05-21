#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <wrl/client.h>

namespace TrepiCoder {
	class Graphics {
	public:
		bool initialize(HWND hwnd, int width, int height);
		void renderFrame();

	private:
		bool initDirectX(HWND hwnd, int width, int height);

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	};
}
