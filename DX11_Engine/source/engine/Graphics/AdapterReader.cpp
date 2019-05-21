#include "engine/Graphics/AdapterReader.h"

namespace TrepiCoder {
	std::vector<AdapterData> AdapterReader::m_adapters;

	std::vector<AdapterData> AdapterReader::getAdapters() {
		if (m_adapters.size() > 0)
			return m_adapters;

		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
		
		// Create a DXGI Factory object
		HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, "Failed to create DXGI Factory for enumerating adapters");
			exit(EXIT_FAILURE);
		}

		IDXGIAdapter* pAdapter;
		UINT index = 0;
		while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter))) {
			m_adapters.push_back(AdapterData(pAdapter));
			index += 1;
		}
		return m_adapters;
	}

	AdapterData::AdapterData(IDXGIAdapter* pAdapter) {
		m_pAdapter = pAdapter;
		HRESULT hr = pAdapter->GetDesc(&m_description);
		if (FAILED(hr))
			ErrorLogger::Log(hr, "Failed to get description for adapter");
	}
}