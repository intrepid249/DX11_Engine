#pragma once
#include <string>

typedef long HRESULT;

namespace TrepiCoder {
	class ErrorLogger {
	public:
		static void Log(std::string message);
		static void Log(HRESULT hr, std::string message);
	};
}