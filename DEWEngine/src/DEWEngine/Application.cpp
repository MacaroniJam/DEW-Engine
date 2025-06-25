#include "dewpch.h"
#include "Application.h"

#include "DEWEngine/Events/ApplicationEvent.h"
#include "DEWEngine/Log.h"

#include <GLFW/glfw3.h>

namespace DEWEngine {

	Application::Application() {
		// Initialize the application

		m_Window = std::unique_ptr<Window>(Window::Create()); // Deletes the window when Application terminates
	}

	Application::~Application() {
		// Clean up resources
	}

	void Application::Run() {
		// Main loop of the application
		while (m_Running) {
			glClearColor(1, 0, 1, 1); // Set clear color to pink
			glClear(GL_COLOR_BUFFER_BIT); // Clear the screen using the specified color

			m_Window->OnUpdate();
		}
	}
}