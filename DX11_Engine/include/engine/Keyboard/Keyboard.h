#pragma once
#include <queue>
#include <memory>

namespace TrepiCoder {
	class KeyboardEvent;

	class Keyboard {
	public:
		Keyboard();

		bool keyIsPressed(const unsigned char keycode);

		bool keyBufferIsEmpty();
		bool charBufferIsEmpty();

		KeyboardEvent readKey();
		unsigned char readChar();

		void onKeyPressed(const unsigned char key);
		void onKeyReleased(const unsigned char key);

		void onChar(const unsigned char key);

		void enableAutoRepeatKeys();
		void disableAutoRepeatKeys();

		void enableAutoRepeatChars();
		void disableAutoRepeatChars();

		bool isKeysAutoRepeat();
		bool isCharsAutoRepeat();

	private:
		bool m_autoRepeatKeys = false;
		bool m_autoRepeatChars = false;
		bool m_keyStates[256];

		std::queue<std::shared_ptr<KeyboardEvent>> m_keyBuffer;
		std::queue<unsigned char> m_charBuffer;
	};
}