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

	bool Graphics::initDirectX(HWND hwnd, int width, int height)
	{
		std::vector<AdapterData> adapters = AdapterReader::getAdapters();

		return true;
	}
}
