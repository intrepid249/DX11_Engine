#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DXGI.lib")

#include <vector>
#include <wrl/client.h>

#include "util/ErrorLogger.h"

namespace TrepiCoder {
	class AdapterData {
	public:
		AdapterData(IDXGIAdapter* pAdapter);
		IDXGIAdapter* m_pAdapter = nullptr;
		DXGI_ADAPTER_DESC m_description;
	};

	class AdapterReader {
	public:
		static std::vector<AdapterData> getAdapters();

	private:
		static std::vector<AdapterData> m_adapters;
	};
}
