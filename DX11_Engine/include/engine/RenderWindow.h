#pragma once
#include <Windows.h>
#include <string>

namespace TrepiCoder {
	class WindowContainer;

	class RenderWindow {
	public:
		RenderWindow();
		~RenderWindow();

		bool initialize(WindowContainer * pWindowContainer, HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height);
		/*
		This function will process messages that the application receives (e.g. Mouse/Keyboard input)
		If the function returns false it will indicate the window has been closed
		If true, it indicates to continue with the window loop
		*/
		bool processMessages();

		/*Get a handle to the window instance*/
		HWND getWindowHandle() const;

	private:
		void registerWindowClass();

		HWND m_handle = NULL; // Handle to this window
		HINSTANCE m_hInstance = NULL; // Handle to application instance

		std::string m_windowTitle = "";
		std::string m_windowClass = "";

		int m_windowWidth = 0;
		int m_windowHeight = 0;
	};
}