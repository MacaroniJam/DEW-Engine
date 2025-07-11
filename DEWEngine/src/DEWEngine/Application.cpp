#include "dewpch.h"
#include "Application.h"


#include "DEWEngine/Log.h"

#include <GLFW/glfw3.h>

namespace DEWEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) // Macro to bind event functions to the application instance

	Application::Application() {
		// Initialize the application

		m_Window = std::unique_ptr<Window>(Window::Create()); // Deletes the window when Application terminates
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {
		// Clean up resources
	}

	void Application::OnEvent(Event& e) {
		//Handle Events
		EventDispatcher dispatcher(e);

		//dispatcher.Dispatch<type>(function)
			//If the event is a certian type, call the specified function
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		DEW_CORE_TRACE("{0}", e);
	}

	void Application::Run() {
		// Main loop of the application
		while (m_Running) {
			glClearColor(1, 0, 1, 1); // Set clear color to pink
			glClear(GL_COLOR_BUFFER_BIT); // Clear the screen using the specified color

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;
	}

	
}