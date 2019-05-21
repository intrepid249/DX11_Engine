#include "engine/Engine.h"
#include "engine/RenderWindow.h"

#include "engine/Keyboard/Keyboard.h"
#include "engine/Keyboard/KeyboardEvent.h"

#include "engine/Mouse/Mouse.h"
#include "engine/Mouse/MouseEvent.h"

#include "engine/Graphics/Graphics.h"


namespace TrepiCoder {
	Engine::Engine() : WindowContainer() {

	}

	Engine::~Engine() {
		
	}

	bool Engine::initialize(HINSTANCE hInstance, std::string windowTitle, std::string windowClass, int width, int height) {
		if (!m_renderWindow->initialize(this, hInstance, windowTitle, windowClass, width, height))
			return false;

		if (!m_gfx->initialize(m_renderWindow->getWindowHandle(), width, height))
			return false;
	}

	bool Engine::pollEventMessages() {
		return m_renderWindow->processMessages();
	}

	void Engine::update() {
#pragma region Keyboard Input
		while (!m_keyboard->charBufferIsEmpty()) {
			unsigned char ch = m_keyboard->readChar();


		}

		while (!m_keyboard->keyBufferIsEmpty()) {
			KeyboardEvent kbe = m_keyboard->readKey();
			unsigned char keycode = kbe.getKeyCode();

			if (keycode == VK_ESCAPE) {
				exit(0);
			}
		}
#pragma endregion
		
#pragma region Mouse Input
		while (!m_mouse->eventBufferIsEmpty()) {
			MouseEvent me = m_mouse->readMouse();
			

		}
#pragma endregion
	}
}