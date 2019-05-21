#pragma once
#include "WindowContainer.h"

#include <Windows.h>
#include <string>



namespace TrepiCoder {
	class Engine : WindowContainer {
	public:
		Engine();
		virtual ~Engine();

		bool initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height);
		bool pollEventMessages();

		void update();
	};
}