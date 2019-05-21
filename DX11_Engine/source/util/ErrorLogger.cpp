#include "util/ErrorLogger.h"
#include "util/StringConverter.h"

#include <Windows.h>
#include <comdef.h>

namespace TrepiCoder {
	void ErrorLogger::Log(std::string message) {
		std::string errorMessage = "Error: " + message;
		MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_ICONERROR);
	}

	void ErrorLogger::Log(HRESULT hr, std::string message) {
		// Create a _com_error property to get information about an error
		_com_error error(hr);

		std::wstring errorMessage = L"Error: " + StringConverter::StringToWide(message) + L"\n" + StringConverter::StringToWide(error.ErrorMessage());

		MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);
	}
}