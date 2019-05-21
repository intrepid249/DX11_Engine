#pragma once
#include <memory>
#include <Windows.h>

namespace TrepiCoder {
	class RenderWindow;
	class Keyboard;
	class Mouse;
	class Graphics;

	class WindowContainer {
	public:
		WindowContainer();
		virtual ~WindowContainer();

		LRESULT windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
	protected:
		std::shared_ptr<RenderWindow> m_renderWindow;
		std::shared_ptr<Keyboard> m_keyboard;
		std::shared_ptr<Mouse> m_mouse;
		std::shared_ptr<Graphics> m_gfx;

	private:

	};
}