#pragma once

#include "Event.h"

#include <sstream>

namespace DEWEngine {

	//--Mouse Button Events--//
	class DEW_API MouseButtonEvent : public Event {

	protected:
		int m_Button;

		MouseButtonEvent(int button)
			: m_Button(button) {

		}
	
	public:

		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput )
	};


	class DEW_API MouseButtonPressedEvent : public MouseButtonEvent {

	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {

		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};


	class DEW_API MouseButtonReleasedEvent : public MouseButtonEvent {

	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {

		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
	

	//--Non Mouse Button Events--//
	class DEW_API MouseMovedEvent : public Event {

	private:
		float m_MouseX, m_MouseY;

	public:

		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {

		}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class DEW_API MouseScrolledEvent : public Event {
	private:
		float m_XOffset, m_YOffset;

	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {

		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};
}
