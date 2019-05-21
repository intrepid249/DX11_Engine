#pragma once

namespace TrepiCoder {
	struct MousePoint {
		int x;
		int y;
	};

	class MouseEvent {
	public:
		enum EventType {
			LPRESS,
			LRELEASE,
			RPRESS,
			RRELEASE,
			MPRESS,
			MRELEASE,
			MWHEELUP,
			MWHEELDOWN,
			MOVE,
			RAW_MOVE,
			INVALID
		};

		/*Default constructor returns an invalid EventType*/
		MouseEvent();
		/*Overloaded constructor builds a MouseEvent with valid EventType and coordinates*/
		MouseEvent(const EventType type, const int x, const int y);

		/*Return whether or not there is a valid event for the mouse*/
		bool isValid() const;

		/*Return the type of MouseEvent*/
		EventType getType() const;
		/*Return the position of the mouse*/
		MousePoint getPos() const;
		/*Return the X coordinate of the mouse*/
		int getX() const;
		/*Return the Y coordinate of the mouse*/
		int getY() const;

	private:
		EventType m_type;
		int m_x, m_y;
	};
}