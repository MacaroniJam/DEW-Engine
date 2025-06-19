#pragma once

#include "DEWEngine/Core.h"

// Headers are temporary and will be removed once precompiled headers are implemented
#include <string>
#include <functional>

namespace DEWEngine {
	// Events are currently blocking, meaning when an event occurs it immediately gets dispatched and must be dealt with
	// right then and there. 

	// For the future, a better strategy might be to buffer events in an event bus and process them during the "event" part
	// of the update stage.

	enum class EventType {
		// "None = 0" is used to indicate no event, so it should be the first event typed
		// and have a value of 0. This is useful for checking if an event has occurred or not.
		None = 0,

		// Window events
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,

		// Application events
		AppTick, AppUpdate, AppRender,

		// Keyboard events
		KeyPressed, KeyReleased,

		// Mouse events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// EventCategory is used to categorize events, which can be useful for filtering events
	// we use enum instead of enum class to allow bitwise operations
	// Bits are used as events can belong to multiple categories
	// so bitwise operations are used to combine categories like AND operations (minus the bits) and OR operations (plus the bits)
	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};


	// ## is used to concatenate tokens in macros.
	// For example, GetStaticType(MouseButtonPressed) will become EventType::MouseButtonPressed

	// # is used to convert a token to a string literal
	// For example, GetName(MouseButtonPressed) will become "MouseButtonPressed"
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// Category flags are the bitwise representation of the event categories
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	

	
	// --- DEWEngine Events System -----	
	// Event is the base class for all events in the DEWEngine framework.
	class DEW_API Event {

		friend class EventDispatcher;

	protected:
		bool m_Handled = false; // Indicates if the event has been handled

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// Checks if the event belongs to a specific category
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category; // Bitwise AND operation to check if the category is set
		}
	};

	// EventDispatcher is a utility class that helps in dispatching events to the appropriate handlers.
	class EventDispatcher {

		template<typename T> // T must be a derived class of Event

		//std::function<bool(T&)> is a standard function that takes a T reference (any event) and returns a bool
			//std::function is used to store a function that can be passed in as a parameter
		using EventFn = std::function<bool(T&)>; 

	private:
		Event& m_Event; // Reference to the event being dispatched


	public:
		// : m_Event(event) = m_Event = event; in function body
		EventDispatcher(Event& event) 
			: m_Event(event) {

		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {

			// Check if the event type matches the type T
			if (m_Event.GetEventType() == T::GetStaticType()) {

				// Cast event to the appropriate function and return its handled results
					// &m_Event takes address of m_Event creating Event*
					// (T*)... casts the Event* to T* (Treat mem location as though it was T)
					// *(...) dereferences the T* to get T&
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	};

	// Exists to allow printing of events to the console or logs
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString(); // Outputs the string representation of the event
	}
	
	/*
	// spdlog updates prevents previous method from working, here is another method to format events as strings
	inline std::string format_as(const Event& e) { return e.ToString(); }
	*/
}