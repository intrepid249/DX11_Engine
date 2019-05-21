#include "engine/WindowContainer.h"
#include "engine/RenderWindow.h"
#include "engine/Keyboard/Keyboard.h"
#include "engine/Mouse/Mouse.h"
#include "engine//Graphics/Graphics.h"

#include "util/ErrorLogger.h"

namespace TrepiCoder {
	WindowContainer::WindowContainer() : m_renderWindow(new RenderWindow()), m_keyboard(new Keyboard()), m_mouse(new Mouse()), m_gfx(new Graphics()) {
		static bool raw_input_initialized = false;
		if (!raw_input_initialized) {
			RAWINPUTDEVICE rid;
			// Register mouse as a raw input device
			rid.usUsagePage = 0x01;
			rid.usUsage = 0x02;
			rid.dwFlags = 0;
			rid.hwndTarget = NULL;

			if (RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE)) == false) {
				// Registration failed
				ErrorLogger::Log(GetLastError(), "Failed to register raw input devices");
				exit(EXIT_FAILURE);
			}
			raw_input_initialized = true;
		}
	}

	WindowContainer::~WindowContainer() {
		
	}

	LRESULT WindowContainer::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg)
		{
		/// KEYBOARD
		case WM_KEYDOWN:
		{
			unsigned char keycode = static_cast<unsigned char>(wParam);
			if (m_keyboard->isKeysAutoRepeat()) {
				m_keyboard->onKeyPressed(keycode);
			}
			else {
				// 30th bit stores 1 if keyDown, 0 if keyUp
				const bool wasPressed = lParam & 0x8000;
				// If it is not an autoRepeat char, dispatch the event
				if (!wasPressed) {
					m_keyboard->onKeyPressed(keycode);
				}
			}
			return 0;
		}
		case WM_KEYUP:
		{
			unsigned char keycode = static_cast<unsigned char>(wParam);
			m_keyboard->onKeyReleased(keycode);
			return 0;
		}
		case WM_CHAR:
		{
			unsigned char ch = static_cast<unsigned char>(wParam);
			if (m_keyboard->isCharsAutoRepeat()) {
				m_keyboard->onChar(ch);
			}
			else {
				// 30th bit stores 1 if keyDown, 0 if keyUp
				const bool wasPressed = lParam & 0x8000;
				// If it is not an autoRepeat char, dispatch the event
				if (!wasPressed) {
					m_keyboard->onChar(ch);
				}
			}
			return 0;
		}

		/// MOUSE
		case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_mouse->onMouseMoved(x, y);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_mouse->onLeftPressed(x, y);
			return 0;
		}
		case WM_LBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_mouse->onLeftReleased(x, y);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_mouse->onRightPressed(x, y);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_mouse->onRightReleased(x, y);
			return 0;
		}
		case WM_MBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_mouse->onMiddlePressed(x, y);
			return 0;
		}
		case WM_MBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			m_mouse->onMiddleReleased(x, y);
			return 0;
		}
		case WM_MOUSEWHEEL:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
				m_mouse->onMouseWheelUp(x, y);
			if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
				m_mouse->onMouseWheelDown(x, y);
			
			return 0;
		}
		case WM_INPUT:
		{
			// Process raw input
			UINT dataSize;
			GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

			if (dataSize > 0) {
				std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
				if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize) {
					RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
					if (raw->header.dwType = RIM_TYPEMOUSE) {
						m_mouse->onRawMouseMoved(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
					}
				}
			}
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}