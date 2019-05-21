#include "engine/Keyboard/KeyboardEvent.h"

namespace TrepiCoder {
	KeyboardEvent::KeyboardEvent() : m_type(EventType::Invalid), m_key(0u) {

	}

	KeyboardEvent::KeyboardEvent(const EventType type, const unsigned char key) : m_type(type), m_key(key) {

	}

	bool KeyboardEvent::isPress() {
		return m_type == EventType::Press;
	}

	bool KeyboardEvent::isRelease() {
		return m_type == EventType::Release;
	}

	bool KeyboardEvent::isValid() {
		return m_type != EventType::Invalid;
	}

	unsigned char KeyboardEvent::getKeyCode() {
		return m_key;
	}
}