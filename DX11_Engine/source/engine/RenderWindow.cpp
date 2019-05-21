#include "engine/RenderWindow.h"
#include "util/StringConverter.h"
#include "util/ErrorLogger.h"

#include "engine/WindowContainer.h"

namespace TrepiCoder {
	RenderWindow::RenderWindow() {

	}

	RenderWindow::~RenderWindow() {
		if (m_handle != NULL) {
			UnregisterClass(m_windowClass.c_str(), m_hInstance);
			DestroyWindow(m_handle);
		}
	}

	bool RenderWindow::initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height) {
		m_hInstance = hInstance;
		m_windowTitle = windowTitle;
		m_windowClass = windowClass;
		
		m_windowWidth = width;
		m_windowHeight = height;

		registerWindowClass();

		// Create a window
		m_handle = CreateWindowEx(
			0, // Default for extended windows style
			m_windowClass.c_str(), // Window class name
			m_windowTitle.c_str(), // Window title name
			WS_CAPTION | WS_SYSMENU, // Windows style
			0, // Window X position
			0, // Window Y position
			m_windowWidth,
			m_windowHeight,
			NULL, // Handle to parent window
			NULL, // Handle to menu or child window identifier. Can be set to NULL and use menu in WindowClassEx 
			m_hInstance, // Handle to the instance of module to be used with this window
			pWindowContainer); // Param to create window

		// Check if window was successfully created
		if (m_handle == NULL) {
			ErrorLogger::Log(GetLastError(), "CreateWindowEx failed for window: " + m_windowTitle);
			return false;
		}

		// Bring the window up on screen and set it as the main focus
		ShowWindow(m_handle, SW_SHOW);
		SetForegroundWindow(m_handle);
		SetFocus(m_handle);

		return true;
	}

	bool RenderWindow::processMessages() {
		// Handle the window messages
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG)); // Initialize the memory structure

		if (PeekMessage(
			&msg, // where to store message (if one exists)
			m_handle, // handle to the window to check messages for
			0, // Minimim Filter Msg Value - Not filtering
			0, // Maximum Filter Msg Value - Not filtering
			PM_REMOVE // Remove message after capturing via PeekMessage
		)) {
			TranslateMessage(&msg); // Translate from virtual key messages to character messages
			DispatchMessage(&msg); // Dispatch message to window process for this window
		}

		// Check if the window was closed
		if (msg.message == WM_NULL) {
			if (!IsWindow(m_handle)) {
				m_handle = NULL;
				UnregisterClass(m_windowClass.c_str(), m_hInstance);
				return false;
			}
		}

		return true;
	}

	HWND RenderWindow::getWindowHandle() const
	{
		return m_handle;
	}

	/*Redirect window messages to the window container class*/
	LRESULT CALLBACK HandleMessageRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		default:
			// Retrieve pointer to window class
			WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			// Forward message to window class handler
			return pWindow->windowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg)
		{
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
			if (pWindow == nullptr) {
				ErrorLogger::Log("Critical Error: Pointer to window null during WC_NCCREATE");
				exit(EXIT_FAILURE);
			}
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMessageRedirect));
			return pWindow->windowProc(hwnd, uMsg, wParam, lParam);
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	void RenderWindow::registerWindowClass() {
		// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/ns-winuser-tagwndclassexa
		// The window class. This has to be filled BEFORE the window can be created
		WNDCLASSEX wc;
		// Flags [Redraw on width/height change from resize/movement]
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		// Pointer to the window processing function for handling messages from this window
		wc.lpfnWndProc = HandleMessageSetup;
		// Number of extra bytes to allocate following the window-class structure
		wc.cbClsExtra = 0;
		// Number of extra bytes to allocate following the window instance
		wc.cbWndExtra = 0;

		// Handle to the instance that contains the window procedure
		wc.hInstance = m_hInstance;
		// Handle to the class icon. Must be a handle to an Icon resource
		wc.hIcon = NULL;
		// Handle to the small icon for the class
		wc.hIconSm = NULL;
		// Handle to the class cursor. If null, an application must explicitly set the cursor shape whenever the mouse moves into the application window
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		// Handle to the class background brush for the window's background colour. When NULL an application must paint its own background colour
		wc.hbrBackground = NULL;
		// Pointer to a null-terminated string for the menu
		wc.lpszMenuName = NULL;
		// Pointer to null-terminated string of our class name
		wc.lpszClassName = m_windowClass.c_str();
		wc.cbSize = sizeof(WNDCLASSEX);

		// Register the class to make it usable
		RegisterClassEx(&wc);
	}
}