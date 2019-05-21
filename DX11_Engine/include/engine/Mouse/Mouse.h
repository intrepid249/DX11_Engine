#pragma once
#include <queue>
#include <memory>

namespace TrepiCoder {
	class MouseEvent;
	struct MousePoint;

	class Mouse {
	public:
		Mouse();
		~Mouse();

		/*Left mouse button pressed*/
		void onLeftPressed(int x, int y);
		/*Left mouse button released*/
		void onLeftReleased(int x, int y);
		/*Right mouse button pressed*/
		void onRightPressed(int x, int y);
		/*Right mouse button released*/
		void onRightReleased(int x, int y);
		/*Middle mouse button pressed*/
		void onMiddlePressed(int x, int y);
		/*Middle mouse button released*/
		void onMiddleReleased(int x, int y);
		/*Mouse scroll up*/
		void onMouseWheelUp(int x, int y);
		/*Mouse scroll down*/
		void onMouseWheelDown(int x, int y);
		/*Mouse moved*/
		void onMouseMoved(int x, int y);
		/*Raw mouse movement*/
		void onRawMouseMoved(int x, int y);

		/*Check state of left mouse button*/
		bool isLeftDown();
		/*Check state of right mouse button*/
		bool isRightDown();
		/*Check state of middle mouse button*/
		bool isMiddleDown();

		/*Return X coordinate*/
		int getX();
		/*Return Y coordinate*/
		int getY();
		/*Return mouse potision*/
		MousePoint getPos();

		/*Check if there are mouse events to process*/
		bool eventBufferIsEmpty();
		MouseEvent readMouse();

	private:
		std::queue<std::shared_ptr<MouseEvent>> m_eventBuffer;
		bool m_leftIsDown, m_rightIsDown, m_middleIsDown;
		int m_x, m_y;
	};
}