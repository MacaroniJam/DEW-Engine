#include "Application.h"

#include "DEWEngine/Events/ApplicationEvent.h"
#include "DEWEngine/Log.h"

namespace DEWEngine {

	Application::Application() {
		// Initialize the application
	}

	Application::~Application() {
		// Clean up resources
	}

	void Application::Run() {
		// Main loop of the application

		//Test event handling
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication)) {

			DEW_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput)) {
			DEW_TRACE(e.ToString());
		}

		while (true) {
			
		}
	}
}