#include "engine/Mouse/MouseEvent.h"

namespace TrepiCoder {
	MouseEvent::MouseEvent() : m_type(INVALID), m_x(-1), m_y(-1) {}

	MouseEvent::MouseEvent(const EventType type, const int x, const int y) : m_type(type), m_x(x), m_y(y) {}

	bool MouseEvent::isValid() const {
		return m_type != INVALID;
	}

	MouseEvent::EventType MouseEvent::getType() const {
		return m_type;
	}

	MousePoint MouseEvent::getPos() const {
		return { m_x, m_y };
	}

	int MouseEvent::getX() const {
		return m_x;
	}

	int MouseEvent::getY() const {
		return m_y;
	}
}