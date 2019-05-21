#include "engine/Mouse/Mouse.h"
#include "engine/Mouse/MouseEvent.h"

namespace TrepiCoder {
	Mouse::Mouse() : m_leftIsDown(false), m_rightIsDown(false), m_middleIsDown(false), m_x(-1), m_y(-1) {}

	Mouse::~Mouse() {}

	void Mouse::onLeftPressed(int x, int y) {
		m_leftIsDown = true;
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::LPRESS, x, y)));
	}

	void Mouse::onLeftReleased(int x, int y) {
		m_leftIsDown = false;
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::LRELEASE, x, y)));
	}

	void Mouse::onRightPressed(int x, int y) {
		m_rightIsDown = true;
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::RPRESS, x, y)));
	}

	void Mouse::onRightReleased(int x, int y) {
		m_rightIsDown = false;
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::RRELEASE, x, y)));
	}

	void Mouse::onMiddlePressed(int x, int y) {
		m_middleIsDown = true;
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::MPRESS, x, y)));
	}

	void Mouse::onMiddleReleased(int x, int y) {
		m_middleIsDown = false;
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::MRELEASE, x, y)));
	}

	void Mouse::onMouseWheelUp(int x, int y) {
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::MWHEELUP, x, y)));
	}

	void Mouse::onMouseWheelDown(int x, int y) {
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::MWHEELDOWN, x, y)));
	}

	void Mouse::onMouseMoved(int x, int y) {
		m_x = x;
		m_y = y;
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::MOVE, x, y)));
	}

	void Mouse::onRawMouseMoved(int x, int y) {
		m_eventBuffer.push(std::shared_ptr<MouseEvent>(new MouseEvent(MouseEvent::RAW_MOVE, x, y)));
	}

	bool Mouse::isLeftDown() {
		return m_leftIsDown;
	}

	bool Mouse::isRightDown() {
		return m_rightIsDown;
	}

	bool Mouse::isMiddleDown() {
		return m_middleIsDown;
	}

	int Mouse::getX() {
		return m_x;
	}

	int Mouse::getY() {
		return m_y;
	}

	MousePoint Mouse::getPos() {
		return { m_x, m_y };
	}

	bool Mouse::eventBufferIsEmpty() {
		return m_eventBuffer.empty();
	}

	MouseEvent Mouse::readMouse() {
		if (eventBufferIsEmpty()) {
			return MouseEvent();
		}
		else {
			MouseEvent e = *(m_eventBuffer.front());
			m_eventBuffer.pop();
			return e;
		}
	}
}