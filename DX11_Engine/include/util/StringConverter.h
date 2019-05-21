#pragma once
#include <string>

namespace TrepiCoder {
	class StringConverter {
	public:
		static std::wstring StringToWide(std::string str);
	};
}