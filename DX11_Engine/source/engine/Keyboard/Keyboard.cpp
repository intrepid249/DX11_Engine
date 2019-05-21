#include "engine/Keyboard/Keyboard.h"
#include "engine/Keyboard/KeyboardEvent.h"

namespace TrepiCoder {
	Keyboard::Keyboard() : m_keyStates() {
		for (int i = 0; i < 256; ++i)
			m_keyStates[i] = false;
	}

	bool Keyboard::keyIsPressed(const unsigned char keycode) {
		return m_keyStates[keycode];
	}

	bool Keyboard::keyBufferIsEmpty() {
		return m_keyBuffer.empty();
	}

	bool Keyboard::charBufferIsEmpty() {
		return m_charBuffer.empty();
	}

	KeyboardEvent Keyboard::readKey() {
		if (keyBufferIsEmpty()) {
			return KeyboardEvent();
		}
		else {
			KeyboardEvent e = *(m_keyBuffer.front());
			m_keyBuffer.pop();
			return e;
		}
	}

	unsigned char Keyboard::readChar() {
		if (charBufferIsEmpty()) {
			return 0u;
		}
		else {
			unsigned char e = m_charBuffer.front();
			m_charBuffer.pop();
			return e;
		}
	}

	void Keyboard::onKeyPressed(const unsigned char key) {
		m_keyStates[key] = true;
		m_keyBuffer.push(std::shared_ptr<KeyboardEvent>(new KeyboardEvent(KeyboardEvent::Press, key)));
	}

	void Keyboard::onKeyReleased(const unsigned char key) {
		m_keyStates[key] = false;
		m_keyBuffer.push(std::shared_ptr<KeyboardEvent>(new KeyboardEvent(KeyboardEvent::Release, key)));
	}

	void Keyboard::onChar(const unsigned char key) {
		m_charBuffer.push(key);
	}

	void Keyboard::enableAutoRepeatKeys() {
		m_autoRepeatKeys = true;
	}

	void Keyboard::enableAutoRepeatChars() {
		m_autoRepeatChars = true;
	}

	void Keyboard::disableAutoRepeatKeys() {
		m_autoRepeatKeys = false;
	}

	void Keyboard::disableAutoRepeatChars() {
		m_autoRepeatChars = false;
	}

	bool Keyboard::isKeysAutoRepeat() {
		return m_autoRepeatKeys;
	}

	bool Keyboard::isCharsAutoRepeat() {
		return m_autoRepeatChars;
	}
}