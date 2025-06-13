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
		KeyPressed, KeyReleased, KeyTyped,

		// Mouse events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

}