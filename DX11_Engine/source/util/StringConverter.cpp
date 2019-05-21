#include "util/StringConverter.h"

namespace TrepiCoder {
	std::wstring StringConverter::StringToWide(std::string str) {
		return std::wstring(str.begin(), str.end());
	}
}