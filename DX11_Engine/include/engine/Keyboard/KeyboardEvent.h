#pragma once

namespace TrepiCoder {
	class KeyboardEvent {
	public:
		enum EventType {
			Press,
			Release,
			Invalid
		};

		KeyboardEvent();
		KeyboardEvent(const EventType type, const unsigned char key);

		bool isPress();
		bool isRelease();
		bool isValid();

		unsigned char getKeyCode();

	private:
		EventType m_type;
		unsigned char m_key;
	};
}